#include "pch.h" 


namespace IControls
{
	namespace SliderView
	{
		public delegate void ItemViewerManipulationStartedEventHandler(Platform::Object^ sender , int32 item);
		public delegate void ItemViewerManipulationFinishedEventHandler(Platform::Object^ sender , int32 item); 

		public delegate void ItemViewerManipulationEnableEventHandler(Platform::Object^ sender , bool _state);

		public ref class ItemViewer sealed : public Windows::UI::Xaml::Controls::Grid
		{
		public:
			ItemViewer(); 
			event ItemViewerManipulationEnableEventHandler ^ ItemViewerManipulationEnable  ;

			void AnimateToFull();
			void AnimateToMedium();
			void SetToLeft();
			void SetToRight();

			property float64 ItemWidth
			{
				void set(float64 value)
				{ 
					this->_itemwidth =  value ; 
					this->Width  =  value ;
				}
				float64 get(){return this->Width ;}
			}
		
			property float64 ItemHeight
			{
				void set(float64 value)
				{
					this->_itemheight = value ;  
					this->Height =  value;
				}
				float64 get(){return this->Height ;}
			}

			property float64 MinScale
			{
				void set(float64 value)
				{
					this->_minscale = value ;   
					//set the scale temporal
					//this->_itemtransform->ScaleX = value ;
					//this->_itemtransform->ScaleY = value ;
					this->_itemtransform->CenterX = _itemwidth / 2 ;
					this->_itemtransform->CenterY = _itemheight / 2; 
				}
				float64 get(){return this->Height ;}
			}


			property float64 DeltaTranslation
			{
				void set(float64 value)
				{
					if(value <= this->Width / 2)
					{
						this->_itemtransform->CenterX = 0.0 ;
						this->_itemtransform->ScaleX = 2*(1 - _minscale ) * value / this->Width + _minscale ;
						this->_itemtransform->ScaleY = this->_itemtransform->ScaleX;
					}
					else
					{
						this->_itemtransform->CenterX = this->Width ;
						this->_itemtransform->ScaleX = 2*(_minscale -1)* value / this->Width + 2.0 - _minscale ;
						this->_itemtransform->ScaleY = this->_itemtransform->ScaleX;
					}
				}
				float64 get(){return 0 ;}
			}

			property int32 ItemNumber
			{
				void set(int32 value){this->_itemnumber = value ; 			}
				int32 get(){return this->_itemnumber ;}
			}

			property Platform::String^ ItemData
			{
				void set(Platform::String^ value){this->_itemcontent->ItemData = value ;}
				Platform::String^ get(){ return this->_itemcontent->ItemData  ;}
			}

		private:

			float64 _itemwidth, _itemheight , _minscale;
			int32 _itemnumber ;
			Windows::UI::Xaml::Controls::Grid ^ _itemcontainer ;
			Windows::UI::Xaml::Media::CompositeTransform^ _itemtransform ;
			///Itemcontent
			ItemViewerContent ^_itemcontent ;

			Windows::UI::Xaml::Media::Animation::Storyboard ^ _animation_story ;
			Windows::UI::Xaml::Media::Animation::DoubleAnimation ^ _scaleanimationX;
			Windows::UI::Xaml::Media::Animation::DoubleAnimation ^ _scaleanimationY;

			void ItemViewerContentUpdateState_1(Platform::String^ sender, bool _value);

			void initanimations();
		};
	}
}