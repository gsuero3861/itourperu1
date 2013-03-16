#include "pch.h"
#include <math.h>

namespace IControls
{
	namespace SliderView
	{

		public enum class SliderManipulationState
		{
			Enable,
			Dislable
		};

		public delegate void SlideViewerItemChangedEventHandler(Platform::Object^ sender,  int32 _item);

		public ref class SlideViewer sealed : public Windows::UI::Xaml::Controls::Grid
		{
		public:
			SlideViewer();

			event SlideViewerItemChangedEventHandler ^ SlideViewerItemChanged ;

			property Windows::Foundation::Collections::IVector<Platform::String^>^ MediumPaths
			{
				void set(Windows::Foundation::Collections::IVector<Platform::String^>^ value)
				{ 
					this->_mediumpaths =  value ;
					loaditems();
				} 
				Windows::Foundation::Collections::IVector<Platform::String^>^ get()
				{ return this->_mediumpaths; }
			}
		 
			property float64 ItemWidth
			{
				void set(float64 value)
				{ 
					this->_itemwidth =  value ;  
					this->_virtualitem_1->Width = abs(_controlwidth - _itemwidth) / 2 ;
					this->_virtualitem_2->Width = abs(_controlwidth - _itemwidth) / 2 ;
					for (int i = 0; i < _itemspanel->Children->Size; i++)
					{
						//set width a cad item 
						((ItemViewer^)(_itemspanel->Children->GetAt(i)))->ItemWidth = value ;
					}
				}
				float64 get(){return this->Width ;}
			}
		
			property float64 ItemHeight
			{
				void set(float64 value)
				{
					this->_itemheight = value ; 
					this->_virtualitem_1->Height = value ;
					this->_virtualitem_2->Height = value ;
					for (int i = 0; i < _itemspanel->Children->Size; i++)
					{
						//set height a cad item 
						((ItemViewer^)_itemspanel->Children->GetAt(i))->ItemHeight = value;
					}
				}
				float64 get(){return this->Height ;}
			}

			property float64 ControlWidth
			{
				void set(float64 value)
				{
					this->_controlwidth = value ; 
					this->_virtualitem_1->Width = abs(_controlwidth - _itemwidth) / 2 ;
					this->_virtualitem_2->Width = abs(_controlwidth - _itemwidth) / 2 ;
					this->Width = value;
				}
				float64 get(){return this->_controlwidth ;}
			}

			property float64 ControlHeight
			{
				void set(float64 value)
				{ 
					this->_controlheight =  value ; 
					this->Height = value ; 
				}
				float64 get(){return this->_controlheight ;}
			}

			property float64 MinScale
			{
				void set(float64 value)
				{ 
					this->_minscale =  value ; 
					for (int i = 0; i < _numberofitems; i++)
						((ItemViewer^)_itemspanel->Children->GetAt(i))->MinScale= value ;
				}
				float64 get(){return this->_controlheight ;}
			}

			property float64 CurrentItem
			{
				void set(float64 value)
				{  //falta setter para cuando ya estan creados
					this->_currentitem = (int32)value ;
					this->_currentitemduplicate = _currentitem ;
					this->_paneltransform->TranslateX = (-1)*_itemwidth * value ;
				}
				float64 get(){return this->_currentitem ;}
			}

			property SliderManipulationState ManipulationsState
			{
				void set(SliderManipulationState value){ _manipulationstate =  value ; }
				SliderManipulationState get(){ return _manipulationstate ; }
			}

		private:
			Windows::Foundation::Collections::IVector<Platform::String^>^  _mediumpaths ;

			Windows::UI::Xaml::Controls::StackPanel^ _itemspanel ;
			Windows::UI::Xaml::Controls::StackPanel^ _scrollpanel ;
			Windows::UI::Xaml::Controls::Grid^ _virtualitem_1 ;
			Windows::UI::Xaml::Controls::Grid^ _virtualitem_2 ;
			Windows::UI::Xaml::Controls::ScrollViewer ^ _scrollviewer ;
		
			Windows::UI::Xaml::Media::CompositeTransform^ _paneltransform ;
			Windows::UI::Xaml::Media::Animation::DoubleAnimation^ _translateanimation ;
			Windows::UI::Xaml::Media::Animation::Storyboard^ _translatestory ;

			float64 _controlwidth, _controlheight ;
			float64 _itemwidth, _itemheight ;
			float64 _minscale;
			float64 _currenttranslate;
			int32  _numberofitems, _numberofpointers, _currentitem , _currentitemduplicate;
			float64 _mintranslate, _maxtranslate;
			float64 _initialtranslate, _finaltranslate ;
		
			void initcontrols() ;
			void loaditems();
			void initstoryboard();
			SliderManipulationState _manipulationstate ;
		

			void Slider_PointerPressed_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
			void Slider_PointerReleased_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
			void Slider_ManipulationDelta_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ e);
			void Slider_ManipulationCompleted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs^ e);
			void Slider_ManipulationInertiaStarting_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationInertiaStartingRoutedEventArgs^ e);

			//Capture event item
			void ItemViewerUpdateState_1(Platform::Object^ sender , bool _value);

		};
	}
}