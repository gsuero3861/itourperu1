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

			property float64 ItemHeight
			{
				void set(float64 value){this->Height = value;}
				float64 get(){return this->Width;}
			}


			property float64 ItemPosition
			{
				void set(float64 value){this->_position = value;}
				float64 get(){return this->_position;}
			}

			property int32 ChapterNumber
			{
				void set(int32 value)
				{
					this->_chapter = value;
					
				}
				int32 get(){return this->_chapter ;}
			}

			property int32 SectionNumber
			{
				void set(int32 value){this->_section = value;}
				int32 get(){return this->_section ;}
			}
			property int32 PageNumber
			{
				void set(int32 value){this->_page = value;}
				int32 get(){return this->_page ;}
			}

			property Platform::String^ Source
			{
				void set(Platform::String^ value)
				{
					Windows::UI::Xaml::Controls::Image^ img = ref new Windows::UI::Xaml::Controls::Image();
					img->Source =  ref new Windows::UI::Xaml::Media::Imaging::BitmapImage(ref new Windows::Foundation::Uri(value));
					img->Width = this->ItemWidth;
					img->Stretch =  Windows::UI::Xaml::Media::Stretch::Fill ;
					this->Height =  this->Height ;
					this->Children->Append(img);
				}
				Platform::String^ get(){return nullptr ;}
			}

			property DataSource::PageDataSource^ ItemDataSource
			{
				void set(DataSource::PageDataSource^ value)
				{
					_datasource = value ;
					loadlargeimage();
				}
				DataSource::PageDataSource^ get(){return _datasource ;}
			}

		private:
			DataSource::PageDataSource^ _datasource ;
			float64 _position ;
			int32 _chapter , _section , _page ;

#pragma endregion

#pragma region Private Methods

		private:
			void loadlargeimage();

#pragma endregion

		};
	}
}