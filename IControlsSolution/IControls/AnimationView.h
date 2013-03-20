#include "pch.h"

namespace IControls
{
	public ref class AnimationView sealed : public Windows::UI::Xaml::Controls::Grid
	{
	public:
		AnimationView();

#pragma region Properties
	public:
		property int32 ThumbWidth
		{
			void set(int32 value){ this->_initialitem =  value ; }
			int32 get(){ return this->_initialitem ;}
		} 
	private:
		int32 _initialitem ;


#pragma endregion

	}; 
}