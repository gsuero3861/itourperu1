#include "pch.h"

using namespace IControls ;
using namespace IControls::ScrollView ;
using namespace IControls::DataSource ;

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
	_manipulationfullgridenable =  false ;

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
	this->_pagedchapters->PagedScrollAnimationOutStarted += ref new PagedScrollAnimationOutStartedEventHandler(this, &IControls::BookViewer::PagedScroll_AnimationOutStarted);
	this->_pagedchapters->PagedScrollAnimationOutCompleted += ref new PagedScrollAnimationOutCompletedEventHandler(this, &IControls::BookViewer::PagedScroll_AnimationOutCompleted);
	this->Children->Append(this->_pagedchapters);   

	this->_animationview =  ref  new AnimationView();
	this->_animationview->AnimationViewCompleted += ref new AnimationViewCompletedEventHandler(this, &IControls::BookViewer::AnimationViewCompleted);
	_animationview->ItemHeight = 900 ;
	_animationview->ItemWidth = 1600 ; 
	this->_animationview->Visibility = Windows::UI::Xaml::Visibility::Collapsed ; 
	this->Children->Append(this->_animationview);

	_fullscrollgrid = ref new Windows::UI::Xaml::Controls::Grid() ;
	this->_fullscrollgrid->Background =  ref new SolidColorBrush(Windows::UI::Colors::Transparent);
	this->_fullscrollgrid->ManipulationMode = ManipulationModes::All ;
	this->_fullscrollgrid->ManipulationCompleted += ref new ManipulationCompletedEventHandler(this, &IControls::BookViewer::FullGrid_ManipulationCompleted_1);
	this->_fullscrollgrid->ManipulationDelta += ref new ManipulationDeltaEventHandler(this, &IControls::BookViewer::FullGrid_ManipulationDelta_1);
	this->_fullscrollgrid->ManipulationInertiaStarting += ref new ManipulationInertiaStartingEventHandler(this, &IControls::BookViewer::FullGrid_ManipulationInertiaStarting_1);
	this->_fullscrollgrid->Visibility = Windows::UI::Xaml::Visibility::Collapsed ;
	this->Children->Append(this->_fullscrollgrid);
	this->_fullpagescroll =  ref new IScrollView();
	this->_fullpagescroll->IScrollViewLockParent += ref new IScrollViewLockParentEventHandler(this, &IControls::BookViewer::IScrollView_LockParent);
	this->_fullpagescroll->IScrollViewUnlockParent += ref new IScrollViewUnlockParentEventHandler(this, &IControls::BookViewer::IScrollView_UnlockParent);
	this->_fullpagescroll->IScrollViewItemChanged += ref new IScrollViewItemChangedEventHandler(this,&IControls::BookViewer::IScrollView_ItemChanged);
	this->_fullscrollgrid->Children->Append(this->_fullpagescroll);
}


void BookViewer::setanimationview()
{
	this->_animationview->Visibility = Windows::UI::Xaml::Visibility::Visible ; 
	_animationview->AnimationSource  = _datasource->Chapters->GetAt(this->_selectedchapter)->Sections->GetAt(this->_selectedsetion);
	_animationview->SetOutAnimation(this->_selectionpage);
	
}
	
void BookViewer::loaddata()
{
	this->_pagedchapters->ChaptersList = _datasource->Chapters ;
}

#pragma endregion


#pragma region Events Methods

void BookViewer::PagedScroll_AnimationOutStarted(Platform::Object^ sender)
{
	this->_selectedchapter = this->_pagedchapters->CurrentChapter ;
	this->_selectedsetion = this->_pagedchapters->CurrentSection ;
	this->_selectionpage = this->_pagedchapters->CurrentPage ;
	
	
}
	
void BookViewer::PagedScroll_AnimationOutCompleted(Platform::Object^ sender)
{
	setanimationview();  
	this->_animationview->AnimateOut(); 
	////creamos el scroll
	this->_fullpagescroll->ScrollHeight = 900 ;
	this->_fullpagescroll->ScrollWidth = 1600 ;
	this->_fullpagescroll->ChaptersList =  _datasource->Chapters ;
	this->_fullpagescroll->CurrentChapter = this->_selectedchapter ;
	this->_fullpagescroll->CurrentSection = this->_selectedsetion ;
	this->_fullpagescroll->CurrentPage = this->_selectionpage ;
}

void IControls::BookViewer::AnimationViewCompleted(Platform::Object ^ sender )
{
	this->_fullscrollgrid->Visibility = Windows::UI::Xaml::Visibility::Visible ;
}


////evenst for full grid

void IControls::BookViewer::FullGrid_ManipulationDelta_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ e)
{}
	
void IControls::BookViewer::FullGrid_ManipulationCompleted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs^ e)
{}
	
void IControls::BookViewer::FullGrid_ManipulationInertiaStarting_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationInertiaStartingRoutedEventArgs^ e)
{}

///events for full scroll
void IControls::BookViewer::IScrollView_LockParent(Platform::Object^ sender, int32 item)
{
}

void IControls::BookViewer::IScrollView_UnlockParent(Platform::Object^ sender, int32 item)
{
}
	
void IControls::BookViewer::IScrollView_ItemChanged(Platform::Object^ sender, int32 item)
{
}

#pragma endregion