#include "pch.h"

namespace IControls
{
	namespace DataSource
	{
		public ref class PageDataSource :  public BindableBase
		{
		public:
			PageDataSource();

#pragma region Properties

		public:
			property Platform::String^ ThumbSource
			{
				void set(Platform::String^ value){ this->_thumbsource = value ; }
				Platform::String^ get(){ return this->_thumbsource ; }
			}

			property Platform::String^ MediumSource
			{
				void set(Platform::String^ value){ this->_mediumsource = value ; }
				Platform::String^ get(){ return this->_mediumsource ; }
			}

			property Platform::String^ FullSource
			{
				void set(Platform::String^ value){ this->_fullsource = value ; }
				Platform::String^ get(){ return this->_fullsource ; }
			}

		private:
			Platform::String^ _thumbsource ;
			Platform::String^ _mediumsource ;
			Platform::String^ _fullsource ;

#pragma endregion
		};
	}
}