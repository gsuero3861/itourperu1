#include "pch.h"

namespace IControls
{
	namespace StackView
	{
		public delegate void StackViewItemManipulationStartedEventHandler(Platform::Object ^ sender , int32 _currentitem);

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class IStackView sealed : public Windows::UI::Xaml::Controls::Grid 
		{
		public:
			IStackView();
		};

	}
}