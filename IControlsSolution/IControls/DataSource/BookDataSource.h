#include "pch.h"

namespace IControls
{
	namespace DataSource
	{
		public ref class BookDataSource :  public BindableBase
		{
		public:
			BookDataSource();

			#pragma region Properties

		public:

			property Platform::String^ Title
			{
				void set(Platform::String^ value){ this->_title = value ; }
				Platform::String^ get(){ return this->_title ; }
			} 

			property Windows::Foundation::Collections::IVector<PageDataSource^>^ Chapters
			{
				void set(Windows::Foundation::Collections::IVector<PageDataSource^>^ value){this->_chapters = value ; }
				Windows::Foundation::Collections::IVector<PageDataSource^>^ get(){ return _chapters ; }
			}

		private:
			Platform::String^ _title ; 
			Windows::Foundation::Collections::IVector<PageDataSource^>^ _chapters ;
			 
#pragma endregion
		};
	}
}