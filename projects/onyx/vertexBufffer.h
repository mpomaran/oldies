// vertexBuffer.h: interface for the dx8Screen class.
//
//////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// Name: class VertexBuffer
// Desc: Klasa przechowuje informacje o vertexach i potrafi je zaladowac
//       do pamieci karty, jesli to konieczne
//
//		init (void *p_vertexData)		- inicjacja bufora (np. kopiowanie do
//										  pamieci karty graficznej)
//		transform (...)					- transformacja (obroty itp.) vertexow
//		operator []						- zwraca dane
//-----------------------------------------------------------------------------

class	VertexBuffer
{
	public:
		void	init (void *p_vertexData) = 0;
		void	transform (void *p_transformData) = 0;

		void*	operator [](int index) = 0;
};