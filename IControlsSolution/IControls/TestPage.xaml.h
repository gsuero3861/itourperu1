//
// TestPage.xaml.h
// Declaration of the TestPage class
//

#pragma once

#include "TestPage.g.h"

namespace IControls
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class TestPage sealed
	{
	public:
		TestPage();

	protected:
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
	private: 
		Platform::Collections::Vector<Platform::String^>^_paths;
		void loaddatasource();
		DataSource::SectionDataSource ^_section1 ;
		DataSource::ChapterDataSource ^_chapter1 ;
		DataSource::BookDataSource ^ _book1 ;
		Platform::Collections::Vector<DataSource::ChapterDataSource^> ^ _chapters ;
	};
}
