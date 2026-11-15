import java.applet.*;
import java.awt.*;
import java.awt.image.*;
import java.net.URL;
import java.lang.Math;

/*
 *
 * Timer of the animation
 *
 */

class AnimateTimer extends Thread {
  boolean pause = false;
  int interval;
  Component drawArea;
  
  public AnimateTimer(Component da, int itime) {
    drawArea = da;
    interval = itime;
  }

  public void run() {
    while (true) {		
      if (!pause)
	drawArea.repaint();
      try { Thread.sleep(interval); } catch (InterruptedException e) {}
    }
  } 

  // sets up the new pace of the simulation
  public void ChangePace(int pace) {
    interval = pace;
  }

  // pauses the timer
  public void Pause() {
    pause = true;
  }

  // resumes the simulation
  public void Resume() {
    pause = false;
  }
}


/*
 *
 * Just wrapper around an integer which allows to pass it by reference 
 *
 */

class IntByRef {
  
  private int value;

  IntByRef(int i) {
    value = i; 
  }

  void Set(int i) {
    value = i;
  }

  int Get() {
    return value;
  }
}



/*
 *
 * This class keeps all configuration constants
 *
 */

class Constants {

  /*
   * One unit of system time is equal to 25*10^-8 sec == .25ms
   */

  /* cable length in meters    */
  static int CableLength;

  /* frame size in bytes      */
  static int FrameSize;

  /* transmission rate in Mbps */
  static int TransmissionRate; 

}



/* 
 * A single insance of a packet
 * A packet has two instances - one goes up, the other - down
 */

class Instance { 

  int X;
  int Y;
  
  // the speed is added to the current coordinates at each update
  // and it defines the direction in which the instance moves
  int speed;
}




/*
 *
 * A single packet is a unit of ethernet frame that propagates along the 
 * line during one unit of system time Each frame consists of multiple 
 * packets. Each packet has 2 instances.
 *
 */  

class Packet {  
  /* 
   * propagation_speed * unit_of_system_time = 50 => 
   * in one unit of system time the signal propagates
   * along the lines for 5 meters
   *
   * 50meters * 200 pixels / cable_length
   */


  /* 
   * the packet propagates along the line for Size pixels 
   * in one unit of system time; we have to round the number up
   */
  static int Speed;
  static int Size;

  // current packet position
  int X;
  int Y;
  
  int S; // which station transmitted the packet
  int F; // number in the frame

  // need 2 instances - one goes up and one down 
  Instance Instances[];
  
  boolean first, last; // is this the first or the last packet in frame?
  Station stations[]; // pointer to all stations

  // which station instance 0 is passing by
  int which0;
  
  // which station instance 1 is passing by
  int which1;

  Packet(int x, int y, int s, Station st[]) { 
    // packet parameters are set up
    // Speed in pixels/unit of simulation time
    // Size of a packet in pixels (= Speed)
    Speed=(int)Math.ceil((double)10000/(double)Constants.CableLength);
    Size =(int)Math.ceil((double)10000/(double)Constants.CableLength);

    // construct a packet leaving a particular station
    
    X = x;
    Y = y;
    S = s; 
    
    int i;

    // initially, assume it is neither first, nor last packet in frame
    first = false;
    last = false;

    stations = st;
    
    // neither instance is passing by any station
    which0 = -1;
    which1 = -1;

    Instances = new Instance[2]; 

    // instances #0 and #1 are the one sitting in the station when we start

    if (S!=0) { // instance #0 goes up
      // station #0 is the uppermost and there's no need for instance #0
      Instances[0] = new Instance();
      Instances[0].X = X + 50 + 10*S; // each - on its own "track"
      Instances[0].Y = Y - Speed; 
      Instances[0].speed = -Speed; // goes up
    }

    if (S!=2) { // instance #1 goes down
      // station #3 is the lowest, there's no need for instance #1
      Instances[1] = new Instance();
      Instances[1].X = X + 50 + 10*S; // each - on its own "track"
      Instances[1].Y = Y;
      Instances[1].speed = Speed; // goes down
    }
  }
  
  boolean Is_Fork (int y) { // has packet reached a fork?
    if (y%100 == 40 && y!= S*100+40)
      // checks if not the station that sent this packet       
      return true;
    else
      return false;
  }
  
  boolean Update () { 
    // update the current positions of each
    // existing instance

    // checks if there either instance is active on the network and 
    // returns the result
    
    // There are two instances: #0 and #1
    // they both reach the bus and then #0 goes up
    // whereas #1 goes down
    
    int i; // for-loop variable

    int lastY_0 = 0, lastY_1 = 0; /* needed for quick fix */

    if ((Instances[0]!=null)&&(Instances[0].Y <= 40)) {
      // reached the upper end; have to kill instance #0
      lastY_0 = Instances[0].Y; /* quick fix - save coordinates */
      Instances[0] = null;
    }

    // reached the lower end; have to kill instance #1
    if ((Instances[1]!=null)&&(Instances[1].Y >= 240)) {
      lastY_1 = Instances[1].Y; /* quick fix - save coordinates */
      Instances[1] = null;
    }

    if (Instances[0]!=null) { // update coordinates
      if (Instances[0].Y + Instances[0].speed > 40)
	Instances[0].Y += Instances[0].speed;
      else 
	Instances[0].Y = 40;
    }
    
    if (Instances[1]!=null) {
      if (Instances[1].Y + Instances[1].speed < 240)
      	Instances[1].Y += Instances[1].speed;
      else {
        Instances[1].Y = 240;
      }
    }

    // check if packet is entering or leaving any stations
    // entering occurs when the first pixel passed the station
    // leaving occurs when the last pixel passed the station
    if(first) { // entering packet
      if ((Instances[0]!=null)&&(Is_Fork(Instances[0].Y))) {
	// we are entering this staion
	stations[(Instances[0].Y - 40)/100].passing_frames++; 
      }  
      if ((Instances[1]!=null)&&(Is_Fork(Instances[1].Y+Speed))) {
	// we are enterling this station
	int st = (Instances[1].Y-40+Speed)/100;
	if (st<0)
	  st = 0;
	if (st>2)
	  st = 2;
	stations[st].passing_frames++;
      }   
    }

    if(last) { // leaving packet
      if ((Instances[0]!=null)&&(Is_Fork(Instances[0].Y+Speed))) {
	// we are leaving this station
	int st = (Instances[0].Y-40+Speed)/100;
	if (st<0)
	  st = 0;
	if (st>2)
	  st = 2;
	if(stations[st].passing_frames>0)
	  stations[st].passing_frames--; 
      }
      
      /* quick fix - last packets's Instance[0] is set to null before
       * it detects that it passed the top most station 
       * therefore, we have to store last coordinates
       */
      if (Instances[0]==null && Is_Fork(lastY_0)) 
	// we are leaving this station
	if (stations[(lastY_0-40)/100].passing_frames>0)
	  stations[(lastY_0-40)/100].passing_frames--;

      if (Instances[1]==null && Is_Fork(lastY_1)) 
	// we are leaving this station
	if((lastY_1-40)/100!=2 &&
	   stations[(lastY_1-40)/100].passing_frames>0) {
	  stations[(lastY_1-40)/100].passing_frames--;
	}

      if ((Instances[1]!=null)&&(Is_Fork(Instances[1].Y))) {
	// we are leaving this station
	int st = (Instances[1].Y-40+Speed)/100;
	if (st<0)
	  st = 0;
	if (st>2)
	  st = 2;
	if(stations[st].passing_frames>0)
	  stations[st].passing_frames--;
      }   
    }

    // now check if either instance is still alive and return the 
    // result

    if((Instances[0]!=null)||(Instances[1]!=null))
      return true;
    else
      return false;
  }
  
  void Draw (Graphics g) {

    // paint both instances    
    if(Instances[0]!=null)
      if(Instances[0].Y>=40)
	g.fillRect(Instances[0].X,Instances[0].Y,10,Size);
    
    if(Instances[1]!=null)
      if(Instances[1].Y+Size<=240)
	g.fillRect(Instances[1].X,Instances[1].Y,10,Size);
      else
	g.fillRect(Instances[1].X,Instances[1].Y,10,240-Instances[1].X);
  }
  
}



/*
 *
 * Ethernet frame class
 *
 */

class EnetFrame {
  
  /* 
   * length of a frame in packets is calculated as
   * FrameSize/(TransmissionRate*unit_of_system_time)
   */

  /* have to round length up */
  int length = 
  (int)Math.ceil((double)(Constants.FrameSize*100)
		 /(double)(Constants.TransmissionRate*25));

  int ID;
  boolean Active;

  // keeps track of which packet has to leave the station  
  Packet packets[] = new Packet[length]; // packet that lives in the frame
  
  // if frame was aborted, it has to stop creating new packets
  boolean abort;

  Station stations[]; // pointer to all stations

  EnetFrame(int x, int y, int s, Station st[]) { 

    int i;
    ID = s;
    Active = false;
    abort = false;
    
    stations = st;

    // create the first packet
    packets[0] = new Packet(305,100*ID+40,ID,stations);
    packets[0].first = true; // mark it as first packet
    
    // if there is only one packet, it is both first and last
    if (length==1)
      packets[0].last = true; 

    // all the rest do not exist yet
    for (i=1;i<length;i++)
      packets[i] = null;    
  }
  
  void Draw(Graphics g){
    int i;

    for (i=0;i<length;i++)
      if (packets[i]!=null) {
	switch(ID) { // set color for each station
	case 0:	
	  if (i % 2 == 0) 
	    g.setColor(new Color(0,255,255));
	  else 
	    g.setColor(new Color(0,180,180));
	  break;
	case 1:	
	  if (i % 2 == 0)
	    g.setColor(new Color(0,255,0));
	  else 
	    g.setColor(new Color(0,180,0));
	  break;
	case 2: 
	  if (i % 2 == 0)
	    g.setColor(new Color(255,0,255));
	  else 
	    g.setColor(new Color(180,0,180));
	  break;
	}

	packets[i].Draw(g); // draw the packet itself
	g.setColor(Color.black);
      }
  }
  
  boolean Update () {
    boolean result = false;
    int i;

    for (i=0;i<length;i++)
      
      if (packets[i]!=null) { // existing packet
	if(packets[i].Update()) // there are alive instances
	  result = true;
	else { // entire packet has reached the appropriate end
	  packets[i] = null;
 	}
      }
      else { // this one does not exist
	if ((i!=0)&& (packets[i-1]!=null)) {  
	  // this one never left the station

	  if (!abort) {
	  // we are not aborting, so we will create new packet now
	  packets[i] = new Packet(305,100*ID+40,ID,stations);
	  if (i==length-1)
	    packets[i].last = true; // mark it as last packet
	  }

	  else { // we are aborting
	    // cut packet's length
	    length = i+1;
	    packets[i-1].last = true; // mark previous as last
	  }
	  
	  return true; // can return immediatelly since we create one by one
	}
      }
    
    return result;
  }
}


/*
 *
 * A transmitting station class
 *
 */

class Station {

  String state_string; // keeps "state" of the station (transmitting, etc.)
  String collisions_string; // string for printing the number of collisions
  String K_string; // string for printing the random number K

  int ID; // station number (0..2)
  EnetFrame e_frame; // the single frame on each station
  // when a collision occurs, the tail of a frame has to keep going
  // till it is off the wire
  // the tail is the part of a frame that is on the wire already
  // when a collision occurred
  EnetFrame tail; 

  boolean active; // was clicked, wants to send

  /* CSMA/CD */
  boolean transmitting; // actually sending
  Station stations[]; // pointer to all stations
  // finishing to transmit all existing packets, no new packets are created
  boolean aborting;

  // counts frames passing by. Channel idle when 0
  // it is updated by a Packet (we pass a reference up to Packet)
  int passing_frames; 
  int collisions;
  boolean waiting; // waiting before retransmitting
  int factor; // 512 bit times, calculated once in the constructor

  int countdown;

  Station(int n, Station st[]) {
    stations = st;
 
    // there's nothing to display on the sidebar originally
    state_string = ""; // state is idle, display nothing
    collisions_string = ""; // no collisions
    K_string = ""; // no random K

    ID = n; // set station number
    active = false;
    e_frame = null;
    tail = null;

    transmitting = false;
    aborting = false;
    waiting = false;
    passing_frames = 0;
    collisions = 0;

    // calculates 512 bit times as
    // ceiling (512/(transmission rate * unit_of_system_time))
    factor =   
      (int)Math.ceil((double)(512*100)/
		     (double)(25*Constants.TransmissionRate));
      
  }
  
  public void Draw(Graphics g){
    // debug
    // g.drawString("pf="+passing_frames,390,ID*100+50);

    if (e_frame!= null) 
      e_frame.Draw(g);

    if (tail != null)
      tail.Draw(g);

    // draw state of the station
    if (state_string.equals("Transmission Complete")) {
      g.setColor(Color.red);
      g.drawString(state_string,150,ID*100+50);
      g.setColor(Color.black);
    }
    else
      g.drawString(state_string,150,ID*100+50);
    
    g.drawString(collisions_string,150,ID*100+60);
    g.drawString(K_string,150,ID*100+70);
  }

  //For drawing random K
  public int K(){

    return 
      (int)Math.round(Math.random()*(Math.pow(2,Math.min(collisions,10))-1));

  }

  public void Update(Graphics g) {
    int i,k;
    
    // no matter in which state the station is, 
    // it has to do an update on the frame tail
    // if it is still on the screen
    // this activity is not affected by any other
    // state changes since a tail is out of
    // control by definition :-)
      if (tail!=null)
	if (!tail.Update())
	  tail = null;

    //If station wants to transmit and the channel is empty.
    //Create a new frame and transmit    
    if (active && passing_frames<=0 && !waiting) {
      if (!transmitting)
	if (e_frame == null) { // the frame doesn't exist yet - create it
	  e_frame = new EnetFrame(305,100*ID+40,ID,stations);
	  transmitting = true;
	  
	  // update the side-bar variables
	  state_string = "Transmitting";
	  K_string = "";

	  // return immediatelly to prevent double update 
	  // by the second if(!e_frame...)-clause when a new frame is created
	  return; 
	}

      if (!e_frame.Update()) { // there are no alive instances
	// we successfully transmitted this frame
	e_frame = null;
	active = false;
	transmitting = false;
	collisions = 0;
	
	// update the side-bar variables
	state_string = "Transmission Complete";
	collisions_string = "";
	K_string = "";
      }
    }

    // Station wants to transmit and channel is busy
    if (active && passing_frames>0 && !transmitting && !waiting) {
      // update the state variable
      state_string = "Busy Channel";
      return; // wait for idle channel
    }

    // Station is transmitting, collision occurred
    if (active && passing_frames>0 && transmitting) {

      // collision, have to abort transmission
      transmitting = false;
      aborting = true;
      e_frame.abort = true;
      collisions++;

      // those bits already on the network have to keep going
      // they are now become tail
      tail = e_frame;
      tail.Update();
      e_frame = null;

      // we start countdown as soon as we detected a collision
      waiting = true;

      // 512 bit times * random K
      k = K(); // save K for drawing on the screen
      countdown = factor*k; 
      
      // update side-bar variables
      if (k == 0) // start retransmission as soon as you detect idle channel
	state_string = "Busy Channel";
      else // entering backoff state
	state_string = "Backoff";
      collisions_string = "Collisions: "+collisions;
      K_string = "K = "+k;
      
      // return to avoid immediate decrement of countdown by 
      // if (waiting) clause below
      return; 
      
    }

    if (aborting) { // have to finish transmitting packets already on wire
	  aborting = false;
    }

    if (waiting)
      if (countdown>0)
	countdown--;
      else 
	waiting = false;
  }
  
  public boolean onClick(int x, int y) {
    // returns true if this station has been clicked 
    // and false if the click was outside of this
    // station's boundaries

    if ((x>=305)&&(x<=345)&&(y>=100*ID+20)&&(y<=100*ID+60)) {
      // this station was clicked
      // activate the packet
      active = true;
      return true;
    }

    else
      return false;
  }

    // end of Station
}





/*
 *
 * Canvas for drawing the network
 *
 */

class NetCanvas extends Canvas {
  Station Stations[]; // transmitting stations

  // the global timer which measures how many milliseconds have elapsed 
  // since the simulation started
  // it is updated every 0.25ms (one unit of simulation time)
  double timer;

  // timer is started when the user clicks on a station
  boolean timer_started; 

  public NetCanvas() {
    super();
    int i;

    timer = 0; // reset the timer
    timer_started = false; // inactive until the user clicks a station
    
    this.setBackground(Color.white);

    Stations = new Station[3];
    
    for(i=0;i<3;i++)
      Stations[i]=null;

  }

  /* ----------------------------------------------- */
  
  // draw all stations and the wire connecting them
  public void drawStations(Graphics g) {
    int i;
    Integer I;
    
    // draw each of the stations and the associated piece of wire
    for (i=0;i<3;i++) {
      I = new Integer(i+1); // to print station number
      
      switch(i+1) { // set color for each station
      case 1:	
	g.setColor(Color.cyan);
	break;
      case 2:	
	g.setColor(Color.green);
	break;
      case 3: 
	g.setColor(Color.magenta);
	break;
      case 4:	
	g.setColor(Color.orange);
	break;	
      }

      g.fillRect(305,i*100+20,40,40); // station
      g.setColor(Color.black); // set the color back to black
      g.drawString(I.toString(),325,i*100+45); // its number
      g.drawLine(345,i*100+40, 350,i*100+40); // connection to the bus
      g.drawString(I.toString(),350+10*i+3,30); // this station's "track"  

    }
    
    // draw the bus connecting stations
    g.drawLine(350,40,350,240);
    
  }

  public void paint(Graphics g) {
    int i;

    // draw the timer title
    g.drawString("Time",10,140);
    g.drawString("(microseconds)",10,150);
    // draw the time reading in red
    g.setColor(Color.red);
    // ""+timer converts long timer to string
    g.drawString(""+(int)Math.floor(timer),10,160); 

    // get the normal color back
    g.setColor(Color.black);

    // update the timer if it has been started
    if (timer_started)
      timer += 0.25; // one unit of simulation time equals .25ms
    
    // draw all the packets currenly on the network
    for(i=0;i<3;i++) 
      if (Stations[i]!=null) {
	Stations[i].Update(g);
	Stations[i].Draw(g);
    }

    drawStations(g);    
  }

}




/*
 *
 * Main class
 *
 */

public class enet extends Applet {

  AnimateTimer runner; // the only thread 
  
  // main panel controls
  // choices - pull-down lists of various parameters
  // buttons - control buttons
  Panel controls, choices, buttons;

  // a separate panel is associated with each pull-down menu
  Panel length_panel, size_panel, rate_panel;
  
  // a separate panel is associated with each panel
  // for each button; this is done to implement
  // multiline labels as two labels added to
  // North South of each _label_panel
  Panel length_label_panel, size_label_panel, rate_label_panel;

  // a separate panel is associated with each button
  Panel start_panel, stop_panel, pause_panel, resume_panel;

  // empty labels used for vertical allignment of buttons and pull-downs
  Panel empty_label1, empty_label2, empty_label3, empty_label4;

  Button Start, Stop, Pause, Resume; // buttons
  Choice Length, Size, Rate; // selection of network parameters

  NetCanvas network; // separate canvas for drawing the network itself

  /* ---- double buffering for removing flicker ---- */
  
  private Image           m_kOffScreenImage = null;
  private Graphics        m_kOffScreenGraphics = null;
  private boolean         m_bResized = true;
  
  /* ----------------------------------------------- */

  public void init() {
    int i;
    
    network = new NetCanvas();

    this.setBackground(Color.white);

    // cable length
    Length = new Choice();
    Length.addItem("100");
    Length.addItem("1000");
    Length.addItem("2500");
    Length.select("2500");

    // frame size
    Size = new Choice();
    Size.addItem("500");
    Size.addItem("1000");
    Size.addItem("5000");
    Size.select("500");

    // transmission rate
    Rate = new Choice();
    Rate.addItem("10");
    Rate.addItem("100");
    Rate.select("10");

    Pause = new Button("Pause");
    Resume = new Button("Resume");
    Start = new Button("Start");
    Stop = new Button("Stop");
    
    // only Start button is active at the beginning
    Pause.disable();
    Resume.disable();
    Stop.disable();

    // create empty labels
    // need to put empty 2-line panels on top of
    // each button to even their position with
    // choice-controls which have 2-line panels on
    // top of them
    empty_label1 = new Panel();
    empty_label1.setLayout(new BorderLayout());
    empty_label1.add("North",new Label(" "));
    empty_label1.add("South",new Label(" "));

    empty_label2 = new Panel();
    empty_label2.setLayout(new BorderLayout());
    empty_label2.add("North",new Label(" "));
    empty_label2.add("South",new Label(" "));

    empty_label3 = new Panel();
    empty_label3.setLayout(new BorderLayout());
    empty_label3.add("North",new Label(" "));
    empty_label3.add("South",new Label(" "));

    empty_label4 = new Panel();
    empty_label4.setLayout(new BorderLayout());
    empty_label4.add("North",new Label(" "));
    empty_label4.add("South",new Label(" "));

    length_label_panel = new Panel();
    length_label_panel.setLayout(new BorderLayout());
    length_label_panel.add("North",new Label("Length",Label.CENTER));
    length_label_panel.add("South",new Label("(meters)",Label.CENTER));

    length_panel = new Panel();
    length_panel.setLayout(new BorderLayout());
    length_panel.add("North",length_label_panel);
    length_panel.add("South",Length);

    size_label_panel = new Panel();
    size_label_panel.setLayout(new BorderLayout());
    size_label_panel.add("North",new Label("Size",Label.CENTER));
    size_label_panel.add("South",new Label("(bits)",Label.CENTER));

    size_panel = new Panel();
    size_panel.setLayout(new BorderLayout());
    size_panel.add("South",Size);
    size_panel.add("North",size_label_panel);

    rate_label_panel = new Panel();
    rate_label_panel.setLayout(new BorderLayout());
    rate_label_panel.add("North",new Label("Rate",Label.CENTER));
    rate_label_panel.add("South",new Label("(Mbps)",Label.CENTER));

    rate_panel = new Panel();
    rate_panel.setLayout(new BorderLayout());
    rate_panel.add("South",Rate);
    rate_panel.add("North",rate_label_panel);

    start_panel = new Panel();
    start_panel.setLayout(new BorderLayout());
    start_panel.add("South",Start);
    start_panel.add("North",empty_label1);

    stop_panel = new Panel();
    stop_panel.setLayout(new BorderLayout());
    stop_panel.add("South",Stop);
    stop_panel.add("North",empty_label2);

    pause_panel = new Panel();
    pause_panel.setLayout(new BorderLayout());
    pause_panel.add("South",Pause);
    pause_panel.add("North",empty_label3);

    resume_panel = new Panel();
    resume_panel.setLayout(new BorderLayout());
    resume_panel.add("South",Resume);
    resume_panel.add("North",empty_label4);

    // all networking parameter controller panel
    choices = new Panel();
    choices.setLayout(new FlowLayout());
    choices.add(length_panel);
    choices.add(size_panel);
    choices.add(rate_panel);

    // all buttons panel
    buttons = new Panel();
    buttons.setLayout(new FlowLayout());
    buttons.add(start_panel);
    buttons.add(stop_panel);
    buttons.add(pause_panel);
    buttons.add(resume_panel);

    // put two panels together
    controls = new Panel();
    controls.setLayout(new FlowLayout());
    controls.setBackground(Color.white);
    controls.add(choices);
    controls.add(buttons);

    this.resize(500,400);
    this.setLayout(new BorderLayout());
    this.add("North",network);
    this.add("South",controls);

  }
  
  public void destroy() {
    if (runner!=null)
      runner.stop();
  }

  /* ---- double buffering for removing flicker ---- */

  public void update( Graphics g )
  {  
    if ( null == m_kOffScreenImage || m_bResized )
      {
	m_kOffScreenImage = createImage( size().width,size().height );
	m_kOffScreenGraphics = m_kOffScreenImage.getGraphics();
	m_bResized = false;
      }
    
    m_kOffScreenGraphics.setColor( getBackground() );
    m_kOffScreenGraphics.fillRect( 0, 0, size().width,size().height );
    m_kOffScreenGraphics.setColor( g.getColor() );
    paint( m_kOffScreenGraphics );
    
    g.drawImage( m_kOffScreenImage, 0, 0, this );
  }
  
  // Display the images
  public void paint(Graphics g) {
    network.paint(g);
  }
  
  public boolean handleEvent(Event e) {
    int i;
    
    switch(e.id) {
    case Event.ACTION_EVENT:
      if (e.target == Start) {
	// get initial parameters and disable their controls
	Constants.CableLength = Integer.parseInt(Length.getSelectedItem());
	Constants.TransmissionRate = Integer.parseInt(Rate.getSelectedItem());
	Constants.FrameSize = Integer.parseInt(Size.getSelectedItem());
	Length.disable();
	Rate.disable();
	Size.disable();

	Start.disable();
	Stop.enable();
	Pause.enable();

	// initialize stations    
	for (i=0;i<3;i++) 
	  network.Stations[i] = new Station (i,network.Stations);
    
	// start the thread with interval expressed in ms
	runner = new AnimateTimer(this,100);
	runner.start(); // start the thread
      }

      if (e.target == Stop) {
	Length.enable();
	Rate.enable();
	Size.enable();

	Start.enable();
	Stop.disable();
	Pause.disable();
	Resume.disable();
	runner.stop();
	
	// destroy stations
	for (i=0;i<3;i++)
	  network.Stations[i] = null;

	// stop the timer
	network.timer_started = false;

	network.timer = 0; // reset the timer value
      }

      if (e.target == Pause) {
	Pause.disable();
	Resume.enable();
	
	runner.Pause();
      }

      if (e.target == Resume) {
	Pause.enable();
	Resume.disable();
	runner.Resume();
      }
      return true;
      
    case Event.MOUSE_DOWN:
      // call each stations's method onClick and let stations 
      // decide which one of them was clicked if any

      for (i=0; i<3; i++) 
	if (network.Stations[i]!=null) 
	  if (network.Stations[i].onClick(e.x,e.y)) // a station was clicked
	    network.timer_started = true;
      return true;
      
    default:
      return false;
    }
  }
}



























