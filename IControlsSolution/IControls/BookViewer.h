#include "pch.h"

namespace IControls
{
	public ref class BookViewer sealed : public Windows::UI::Xaml::Controls::Grid
	{
	public:
		BookViewer();

#pragma region Properties

	public:

		property float64 BookHeight
		{
			void set(float64 value)
			{
				this->_bookheight =  value ;
				this->_pagedchapters->ScrollHeight =  this->_bookheight ;
			}
			float64 get(){return this->_bookheight;}
		}

		property float64 BookWidth
		{
			void set(float64 value)
			{
				this->_bookwidth =  value ;
				this->_pagedchapters->ScrollWidth = this->_bookwidth ;
			}
			float64 get(){return this->_bookwidth;}
		}

		property int32 SelectedChapter
		{
			void set(int32 value){ this->_selectedchapter =  value ;}
			int32 get(){return this->_selectedchapter;}
		}

		property int32 SelectedSection
		{
			void set(int32 value){ this->_selectedsetion =  value; }
			int32 get(){return this->_selectedsetion ;}
		}
		
		property int32 SelectedPage
		{
			void set(int32 value){ this->_selectionpage =  value ; }
			int32 get(){return this->_selectionpage ;}
		}

		property DataSource::BookDataSource^ BookSource
		{
			void set(DataSource::BookDataSource^ value)
			{
				this->_datasource = value ;
				loaddata();
			}
			DataSource::BookDataSource^ get(){ return _datasource ; }
		}

	private:
		float64 _bookwidth, _bookheight ;
		int32 _selectedchapter , _selectedsetion, _selectionpage ;
		DataSource::BookDataSource^ _datasource ;
#pragma endregion

#pragma region Controls

	private:
		PagedScroll ^ _pagedchapters ;
		Windows::UI::Xaml::Controls::StackPanel ^ _animationpanel ;
		///ScrollViewer

		
#pragma endregion
 

#pragma region Private Methods

	private:
		void setcurrentpage(int32 _chapter, int32 _section, int32 _page );
		void initcontrols();
		void loaddata();

#pragma endregion

	};
}