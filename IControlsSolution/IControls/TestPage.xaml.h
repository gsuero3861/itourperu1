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
		void Grid_ManipulationCompleted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs^ e);
		void Grid_ManipulationDelta_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ e);
		void Grid_ManipulationInertiaStarting_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationInertiaStartingRoutedEventArgs^ e);
		Platform::Collections::Vector<Platform::String^>^_paths;
	};
}
