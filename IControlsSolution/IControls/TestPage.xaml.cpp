//
// TestPage.xaml.cpp
// Implementation of the TestPage class
//

#include "pch.h"
#include "TestPage.xaml.h"

using namespace IControls;
using namespace IControls::DataSource ;
using namespace IControls::ScrollView ;

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

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

TestPage::TestPage()
{
	InitializeComponent();
	_paths = ref new Platform::Collections::Vector<Platform::String^>();
	for (int i = 11; i < 33; i++)
	{
		_paths->Append("ms-appx:///images/mybook/Image000"+ i +".png");
	} 
	loaddatasource(); 
	//scrollview1->ItemsList = _paths ;
	/** scrollview1->ScrollHeight = 900 ;
	scrollview1->ScrollWidth = 1600 ;
	scrollview1->ChaptersList = _chapters ;
	scrollview1->CurrentChapter = 0 ;
	scrollview1->CurrentSection = 1 ;
	scrollview1->CurrentPage = 2 ;
	 */
	
	//stackview1->StackDataSource = _section1 ;

	//stackscroll1->ScrollWidth = 1600 ;
	//stackscroll1->ScrollHeight = 900 ;
	//stackscroll1->ChapterSource = _chapter1 ; 
	//pagedscroll1->ChaptersList = _chapters ;

	bookviewer1->BookHeight = 900 ;
	bookviewer1->BookWidth = 1600 ;
	bookviewer1->BookSource = _book1 ;

	/**
	animationview1->ItemHeight = 900 ;
	animationview1->ItemWidth = 1600 ;
	animationview1->AnimationSource = _section1 ;
	animationview1->SetOutAnimation(1);*/
}

/// <summary>
/// Invoked when this page is about to be displayed in a Frame.
/// </summary>
/// <param name="e">Event data that describes how this page was reached.  The Parameter
/// property is typically used to configure the page.</param>
void TestPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	(void) e;	// Unused parameter
}

void TestPage::loaddatasource()
{
	SectionDataSource^ _section3 = ref new SectionDataSource();
	_section1 = ref new SectionDataSource();
	_section1->Title = "Section1" ;
	Platform::Collections::Vector<PageDataSource^>^ _pages1 =  ref new Platform::Collections::Vector<PageDataSource^> () ;
	for (int i = 1; i <= 6; i++)
	{
		PageDataSource^ page1 = ref new PageDataSource();
		page1->ThumbSource = "ms-appx:///images/tmp/thumb"+ i +".png" ;
		page1->FullSource = "ms-appx:///images/tmp/large"+ i +".png" ;
		page1->PageWidth = 1200 ;
		if(i==1 || i == 6 )
			page1->PageWidth = 1600 ;
		page1->PageHeight = 900 ;
		_pages1->Append(page1);
	}
	_section1->Pages = _pages1 ;
	_section3->Pages = _pages1 ;

	SectionDataSource^ _section2 = ref new SectionDataSource();
	SectionDataSource^ _section4 = ref new SectionDataSource();
	_section1->Title = "Section1" ;
	Platform::Collections::Vector<PageDataSource^>^ _pages2 =  ref new Platform::Collections::Vector<PageDataSource^> () ;
	for (int i = 1; i <= 7; i++)
	{
		PageDataSource^ page1 = ref new PageDataSource();
		page1->ThumbSource = "ms-appx:///images/tmp/thumb"+ i +".png" ;
		page1->FullSource = "ms-appx:///images/tmp/large"+ i +".png" ;
		page1->PageWidth = 1200 ;
		if(i==1 || i == 7 )
			page1->PageWidth = 1600 ;		
		page1->PageHeight = 900 ;
		_pages2->Append(page1);
	}
	_section2->Pages = _pages2 ;
	_section4->Pages = _pages2 ;

	Platform::Collections::Vector<SectionDataSource^>^ _sections =  ref new Platform::Collections::Vector<SectionDataSource^> () ;
	_chapter1 = ref new ChapterDataSource();
	_chapter1->Title = "Chapter 1";
	_sections->Append(_section1);
	_sections->Append(_section2);
	_sections->Append(_section3);
	_sections->Append(_section4);
	_chapter1->Sections = _sections ;

	ChapterDataSource^_chapter2 = ref new ChapterDataSource();
	ChapterDataSource^_chapter3 = ref new ChapterDataSource();
	_chapter2->Sections = _sections ;
	_chapter3->Sections = _sections ;

	_chapters =  ref new Platform::Collections::Vector<DataSource::ChapterDataSource^>();
	_chapters->Append(_chapter1);
	_chapters->Append(_chapter2);
	_chapters->Append(_chapter3);


	_book1 = ref new BookDataSource();
	_book1->Title = "title 1" ;
	_book1->Chapters = _chapters ;

}