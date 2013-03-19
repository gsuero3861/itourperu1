#include "pch.h"

namespace IControls
{
	namespace DataSource
	{
		public ref class PageDataSource  sealed :  public BindableBase
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
			property Platform::String^ FullSource
			{
				void set(Platform::String^ value){ this->_fullsource = value ; }
				Platform::String^ get(){ return this->_fullsource ; }
			}


		private:
			Platform::String^ _thumbsource ; 
			Platform::String^ _fullsource ;

#pragma endregion
		};
	}
}