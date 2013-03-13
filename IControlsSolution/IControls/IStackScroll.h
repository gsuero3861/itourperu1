#include "pch.h"

namespace IControls
{

	public enum class ScrollManipulationState
	{ Enable, Dislable };

	public enum class ScrollDeltaType
	{ Normal, Inertia };

	public enum class ScrollManipulationSide
	{ Inside, Outside };

	public enum class ScrollStackTouches
	{ Zero, One, Many };

	public ref class IStackScroll sealed : Windows::UI::Xaml::Controls::Grid
	{
	public :

		IStackScroll();
		void additem(Windows::UI::Xaml::Controls::Grid^ item);


#pragma region Stack Scroll 

	private:

		Windows::UI::Xaml::Controls::Grid^ _scrollgrid;
		Windows::UI::Xaml::Controls::StackPanel^ _panelstacks ;
		Windows::UI::Xaml::Controls::ScrollViewer^ _scrollviewer ;
		void initscrollcontrols();

		Windows::UI::Xaml::Media::CompositeTransform^ _paneltransform ;
	
#pragma endregion


#pragma region Stack Scroll Temporal Data Load

	public:
		property Windows::Foundation::Collections::IVector<Platform::String^>^ ItemsList
		{
			void set(Windows::Foundation::Collections::IVector<Platform::String^>^ value)
			{
				this->_itemslist = value ;
				loaditems();
			}
			Windows::Foundation::Collections::IVector<Platform::String^>^ get(){ return this->_itemslist ; }
		}

	private:
		Windows::Foundation::Collections::IVector<Platform::String^>^ _itemslist ;
		void loaditems();
#pragma endregion


#pragma region Stack Scroll Animations

	private:
		Windows::UI::Xaml::Media::Animation::Storyboard^ _panelstory;
		Windows::UI::Xaml::Media::Animation::DoubleAnimation^ _panelanimation ;
		void initanimationproperties();

#pragma endregion


#pragma region Stack Scroll Public Properties

	public:
		property float64  ScrollWidth
		{
			void set(float64 value)
			{
				this->_scrollviewer->Width = value ;
				this->_scrollgrid->Width = value ;
				this->_panelstacks->Width = 4 * value ;
				this->_finaltranslate = -3 * value ;
			}
			float64 get(){return this->_scrollviewer->Width ;}
		}

		property float64  ScrollHeight
		{
			void set(float64 value)
			{
				this->_scrollviewer->Height = value ;
				this->_scrollgrid->Height = value ;
				this->_panelstacks->Height =  value ;
			}
			float64 get(){return this->_scrollviewer->Width ;}
		}

	private:


#pragma endregion

#pragma region Stack Scroll Private Properties

	private:
		ScrollManipulationState _scrollmanipulationstate ;
		ScrollManipulationSide _scrollmanipulationside ;
		ScrollDeltaType _scrolldeltatype ;
		ScrollStackTouches _scrolltouches ;
		
		int32 _numberoftouches ;
		float64 _initialtranslate, _finaltranslate , _currenttrnaslate, _currentdelta;


#pragma endregion
		
#pragma region Stack Scroll Private Methods

	private:
 
		void Panel_ManipulationCompleted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs^ e);
		void Panel_ManipulationDelta_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ e);
		void Panel_ManipulationInertiaStarting_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationInertiaStartingRoutedEventArgs^ e);
		void Panel_PointerReleased_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void Panel_PointerPressed_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);

		void initprivateproperties() ;
		
#pragma endregion

#pragma region Pointer Pressed  Functions

	public:
		typedef bool (IStackScroll:: * PointerFunctions)();
		bool zeropressed();
		bool onepressed();
		bool manypressed();

		bool onereleased();
		bool manyreleased();

	private:
		PointerFunctions _pointerpressedfunctions[3] ;
		PointerFunctions _pointerreleasedfunctions[2];
		void initpointerfunctions(); 

#pragma endregion


	};
}