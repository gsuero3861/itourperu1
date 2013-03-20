#include "pch.h"

namespace IControls
{
	public ref struct IControlsItemChangedEventArgs sealed
	{
	public: 

		property int16 Page
		{
			void set(int16  value){	_page =  value ;}
			int16 get()	{return _page ;	}
		}

		property int16 Section
		{
			void set(int16  value){	_section =  value ;}
			int16 get()	{return _section ;	}
		}

		property int16 Chapter
		{
			void set(int16  value){	_chapter =  value ;}
			int16 get()	{return _chapter ;	}
		}

	private:
		int32 _page, _chapter, _section ;
	};

	public delegate void IControlsItemChangedEventHandler(Platform::Object^ sender ,  IControlsItemChangedEventArgs ^ e ) ;

	/**
	public ref struct Frame
	{
	public :

		property float64 X
		{
			void set(float64 value){  }
			float64 get(){}
		}

		property float64 Y
		{
			void set(float64 value){}
			float64 get(){}
		}

		property float64 Width
		{
			void set(float64 value){}
			float64 get(){}
		}

		property float64 Height
		{
			void set(float64 value){}
			float64 get(){}
		}
		
	private:
		float64 _height, _width, _x , _y;
	};

	public ref struct Layer
	{
	public:
		property Frame^ thumbframe;
		property String thumbpath;
		property Frame^ largeframe;
		property String largepath;//.mp4
	};

	public ref struct Page
	{
		property Frame^ backgroundFrame;
		property Platform::String^ backgroundImage;
		property Windows::Foundation::Collections::IVector<Platform::String^>^ layers;
		property Windows::Foundation::Collections::IVector< Layer ^ > layers;
	};
	*/
//	Page page;


}