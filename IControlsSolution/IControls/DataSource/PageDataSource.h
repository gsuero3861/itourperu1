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
		

			property Platform::Object^ FullView
			{
				void set(Platform::Object^ value){}
				Platform::Object^ get(){return nullptr ;}
			}

			property float64 PageHeight
			{
				void set(float64 value){ this->_height =  value ;}
				float64 get(){ return this->_height ;}
			}

			property float64 PageWidth
			{
				void set(float64 value){ this->_width = value ;}
				float64 get(){ return this->_width ;}
			}

			property float64 ThumbHeight
			{
				void set(float64 value){ this->_thumbheight =  value ;}
				float64 get(){ return this->_thumbheight ; }
			}

			property float64 ThumbWidth
			{
				void set(float64 value){ this->_thumbwidth =  value ; }
				float64 get(){ return this->_thumbwidth ;}
			}


		private:
			Platform::String^ _thumbsource ; 
			Platform::String^ _fullsource ;
			float64 _width, _height , _thumbheight , _thumbwidth ; 

#pragma endregion
		};
	}
}