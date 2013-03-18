#include "pch.h" 

namespace IControls
{
	namespace ScrollView
	{
		public ref class IScrollViewItem sealed : public Windows::UI::Xaml::Controls::Grid
		{
		public:
			IScrollViewItem();

#pragma region Public Properties

		public:
			property float64 ItemWidth
			{
				void set(float64 value){this->Width = value;}
				float64 get(){return this->Width;}
			}

#pragma endregion
		};
	}
}