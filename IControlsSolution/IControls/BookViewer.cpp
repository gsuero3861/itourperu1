#include "pch.h"

using namespace IControls ;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

BookViewer::BookViewer()
{
	initcontrols();
}


#pragma region Private Methods

void BookViewer::setcurrentpage(int32 _chapter, int32 _section, int32 _page )
{
	this->_selectedchapter = _chapter ;
	this->_selectedsetion = _section ;
	this->_selectionpage = _page ;
}

void BookViewer::initcontrols()
{

	this->_pagedchapters =  ref new PagedScroll();
	this->Children->Append(this->_pagedchapters); 
	this->_animationpanel = ref new StackPanel();
}
	
void BookViewer::loaddata()
{
	this->_pagedchapters->ChaptersList = _datasource->Chapters ;
}

#pragma endregion