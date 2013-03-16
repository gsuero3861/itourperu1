#include "pch.h" 


namespace IControls
{
	namespace SliderView
	{

		public enum class ItemContentManipulationState
		{
			Dislable,//this item is not being manipulating
			Enable	//this item is being manipulating
		};

		//true -> this item is being manipulated
		public delegate void ItemViewerContentManipulationEnableEventHandler(Platform::Object^ sender ,   bool _state);

		public ref class ItemViewerContent sealed : public Windows::UI::Xaml::Controls::Grid
		{
		public:
			ItemViewerContent();
			event ItemViewerContentManipulationEnableEventHandler ^ ItemViewerContentManipulationEnable ;
			property Platform::String^ ItemData
			{
				void set(Platform::String^ value)
				{
					this->_itemdata =  value ;
					loaditem();
				}
				Platform::String^ get(){ return this->_itemdata ; ;}
			}

		private:
			Platform::String ^ _itemdata ;

#pragma region ImageItem

		private:
		
			Windows::UI::Xaml::Controls::Image ^ _itemimage ;
			void loaditem();
#pragma endregion

		};
	}
}