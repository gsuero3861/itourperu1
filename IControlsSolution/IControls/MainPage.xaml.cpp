//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

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

MainPage::MainPage()
{
	InitializeComponent(); 
	Grid ^ a = ref new Grid();
	a->Background = ref new SolidColorBrush(Windows::UI::Colors::Aqua);
	a->Height =500 ;
	a->Width = 1500 ;
	Grid ^ b = ref new Grid();
	b->Background = ref new SolidColorBrush(Windows::UI::Colors::Red);
	b->Height =500 ;
	b->Width = 1500 ;
	Grid ^ c = ref new Grid();
	c->Background = ref new SolidColorBrush(Windows::UI::Colors::Blue);
	c->Height =500 ;
	c->Width = 1500 ;
	Grid ^ d = ref new Grid();
	d->Height =500 ;
	d->Width = 1500 ;
	d->Background = ref new SolidColorBrush(Windows::UI::Colors::Aqua);
	stackscroll1->additem(a);
	stackscroll1->additem(b);
	stackscroll1->additem(c);
	stackscroll1->additem(d);
}

/// <summary>
/// Invoked when this page is about to be displayed in a Frame.
/// </summary>
/// <param name="e">Event data that describes how this page was reached.  The Parameter
/// property is typically used to configure the page.</param>
void MainPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	(void) e;	// Unused parameter
}
