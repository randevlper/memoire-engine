#pragma once
#include <string>
#include <filesystem>
#include <sstream>
#include <vector>
namespace lb {
	namespace imgui {
		namespace utilities {
			std::string selectFile(bool& isOpen, std::filesystem::directory_entry& directory, std::string folder, std::string fileExt);
			//bool AddItemButton();
			
			template<class T>
			void MoveItemUp(std::vector<T>& data, int& selection) {
				//Check where the element is at and attemt to move it above
				int spot = selection - 1;
				if (spot < 0) { spot = 0; };
				std::vector<T>::iterator it = data.begin() + spot;
				data.insert(it, data[selection]);

				it = data.begin() + selection + 1;
				data.erase(it);

				if (spot != 0) {
					selection -= 1;
				}
				else {
					selection = 0;
				}
			}

			template<class T>
			void MoveItemDown(std::vector<T>& data, int& selection) {
				int spot = selection + 2;
				if (spot >= data.size()) {
					data.push_back(data[selection]);
					std::vector<T>::iterator it = data.begin() + selection;
					data.erase(it);

					selection = data.size() - 1;

				}
				else {
					std::vector<T>::iterator it = data.begin() + spot;
					data.insert(it, data[selection]);

					it = data.begin() + selection;
					data.erase(it);

					selection += 1;
				}
			}
			
			template <class T>
			void DupeItem(std::vector<T>& data, int& selection) {
				//Check where the element is at and attemt to move it below
				int spot = selection + 1;
				if (spot >= data.size()) {
					data.push_back(data[selection]);
					std::vector<DialogueLine>::iterator it = data.begin() + selection;
				}
				else {
					std::vector<DialogueLine>::iterator it = data.begin() + spot;
					data.insert(it, data[selection]);
				}
				data[spot].name += +"_copy";
			}
		}
	}
}
