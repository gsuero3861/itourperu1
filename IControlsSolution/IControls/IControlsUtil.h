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


}