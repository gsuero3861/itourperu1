#include  "pch.h"

namespace IControls
{

	public delegate void PagedScrollItemLockParentEventHandler(Platform::Object^ sender,  int32 _item);
	public delegate void PagedScrollItemUnlockParentEventHandler(Platform::Object^ sender,  int32 _item);


	public ref class PagedScrollItem sealed : public Windows::UI::Xaml::Controls::Grid
	{
	public:
		PagedScrollItem();
		event PagedScrollItemLockParentEventHandler ^ PagedScrollItemLockParent ;
		event PagedScrollItemUnlockParentEventHandler ^ PagedScrollItemUnlockParent ;

#pragma region Controls
	private:
		
		Windows::UI::Xaml::Controls::Grid^ _stackscrollgrid ;
		void initcontrols();

#pragma endregion

#pragma region Public Properties

	public:
		property float64 ItemWidth
		{
			void set(float64 value){ this->_itemwidth =  value ;}
			float64 get(){return this->_itemwidth;}
		}

		property float64 ItemHeight
		{
			void set(float64 value){ this->_itemheight =  value ;}
			float64 get(){return this->_itemheight ;}
		}

		property int32 ItemNumber
		{
			void set(int32 value){ this->_itemnumber =  value ;}
			int32 get(){return this->_itemnumber ;}
		}

		

	private:
		float64 _itemwidth, _itemheight ;
		int32 _itemnumber ;

#pragma endregion

#pragma region StackScroll Public Properties

	public:
		property float64 StackHeight
		{
			void set(float64 value){ this->_stackscrollgrid->Width =  value ;}
			float64 get(){return this->_stackscrollgrid->Width ;}
		} 
#pragma endregion

#pragma region StackScroll Private Methods
	private:
		void StackScroll_LockParent(Platform::Object^ sender,  int32 _item);
		void StackScroll_UnlockParent(Platform::Object^ sender,  int32 _item);

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

#pragma region StackScroll Private  properties

	private : 
		IStackScroll^ _stackscroll ; 
#pragma endregion

	};
}