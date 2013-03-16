//
// TestPage.xaml.cpp
// Implementation of the TestPage class
//

#include "pch.h"
#include "TestPage.xaml.h"

using namespace IControls;

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
	for (int i = 0; i < 8; i++)
	{
		_paths->Append("ms-appx:///images/img"+ i +".png");
	}

	slider1->ItemHeight = 900 ;
	slider1->ItemWidth = (900.0/800.0)* 1200;//1024  ;
	slider1->ControlHeight = 900 ;
	slider1->ControlWidth = 1600 ;
	slider1->MinScale = 0.9 ;
	slider1->CurrentItem = 5 ;
	slider1->MediumPaths = _paths ;
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


void IControls::TestPage::Grid_ManipulationCompleted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs^ e)
{
	transform1->TranslateX = 0.0 ;
	transform1->TranslateY = 0.0 ;
	transform1->ScaleX = 1.0 ;
	transform1->ScaleY = 1.0 ;
}


void IControls::TestPage::Grid_ManipulationDelta_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ e)
{
	transform1->TranslateX += e->Delta.Translation.X ;
	transform1->TranslateY += e->Delta.Translation.Y ;
	transform1->ScaleX *= e->Delta.Scale ;
	transform1->ScaleY *= e->Delta.Scale ;
}


void IControls::TestPage::Grid_ManipulationInertiaStarting_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationInertiaStartingRoutedEventArgs^ e)
{
	e->TranslationBehavior->DesiredDeceleration = 300.0 * 96.0 / (1000.0 * 1000.0);
	e->ExpansionBehavior->DesiredDeceleration = 400.0 * 96.0 / (1000.0 * 1000.0); 
}
