#include <cstdlib>
#include <memory>
#include <list>
#include <cstddef>
#include <utility>
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <functional>
#include <execution>

class DutyItem {
public:
	std::filesystem::path copyDir;
	DutyItem(std::filesystem::path && a) :copyDir(std::move(a)) {}
	DutyItem(const std::filesystem::path & a) :copyDir(a) {}
	DutyItem(const DutyItem &) = default;
	DutyItem(DutyItem &&) = default;
	DutyItem&operator=(const DutyItem &) = default;
	DutyItem&operator=(DutyItem &&) = default;
};

class Duty {
public:
	std::filesystem::path toDir;
	std::filesystem::path fromDir;
	std::list<DutyItem> items;
	inline void copy() const;
private:
	class CopyInformation {
	public:
		std::list<std::filesystem::path> dirs;
		std::list<std::filesystem::path> files;
	};
	inline void _p_copy_files(const CopyInformation &) const;
	inline void _p_create_dirs(const CopyInformation &) const;
	inline static void _p_copy_a_file(const std::filesystem::path &, const std::filesystem::path &);
	inline static CopyInformation _p_get_dir_copy_information(const std::filesystem::path &, const std::filesystem::path &);
};

//#define INSTALL_LOG_DEBUG 1

int main(int argc, char ** argv) try {

	const auto varToDir = std::filesystem::u8path(ToDir);
#ifdef INSTALL_LOG_DEBUG
	std::ofstream varLogStream{ varToDir / u8R"(install.log)",std::ios::binary };
#endif
	Duty duty;

	if (argc < 3) {
#ifdef INSTALL_LOG_DEBUG
		varLogStream << "do not input root dir:copy dir" << std::endl;
#endif
		return 0;
	}
	else {
#ifdef INSTALL_LOG_DEBUG
		varLogStream << "copy dir:" << std::endl;
#endif
		duty.toDir = varToDir;
		duty.fromDir = std::filesystem::u8path(argv[1]);
		for (int i = 2; i < argc; ++i) {
			const auto & varI = duty.items.emplace_back(std::filesystem::u8path(argv[i]));
#ifdef INSTALL_LOG_DEBUG
			varLogStream << varI.copyDir << std::endl;
#else
			(void)varI;
#endif
		}
#ifdef INSTALL_LOG_DEBUG
		varLogStream << std::endl;
#endif
	}

	duty.copy();

	return 0;

}
catch (...) {
	return 0;
}


inline void Duty::copy() const {
	for (const auto & varItem : items) {
		const auto varCI = _p_get_dir_copy_information(this->fromDir, this->fromDir / varItem.copyDir);
		_p_create_dirs(varCI);
		_p_copy_files(varCI);
	}
}

inline void  Duty::_p_create_dirs(const CopyInformation & items) const {
	for (const auto & i : items.dirs) {
		try {
			std::filesystem::create_directories(toDir / i);
		}
		catch (...) {}
	}
}

inline Duty::CopyInformation Duty::_p_get_dir_copy_information(const std::filesystem::path & root, const std::filesystem::path & arg) try {
	class FileItem {
	public:
		std::filesystem::path path;
		FileItem(std::filesystem::path && a) :path(std::move(a)) {}
		FileItem(const std::filesystem::path & a) :path(a) {}
		FileItem(const FileItem &) = default;
		FileItem(FileItem&&) = default;
		FileItem&operator=(const FileItem &) = default;
		FileItem&operator=(FileItem &&) = default;
	};

	std::list<FileItem> items;
	items.emplace_back(arg);
	Duty::CopyInformation ans;
	ans.dirs.push_back(std::filesystem::relative(arg, root));

	while (false == items.empty()) {
		FileItem item = items.front();
		items.pop_front();
		std::filesystem::recursive_directory_iterator varRDI(item.path);
		for (const auto & varI : varRDI) {
			if (varI.is_directory()) {
				const auto & varPath = items.emplace_back(varI.path());
				ans.dirs.push_back(std::filesystem::relative(varPath.path, root));
			}
			else {
				ans.files.push_back(std::filesystem::relative(varI.path(), root));
			}
		}
	}

	return std::move(ans);
}
catch (...) {
	return{};
}

inline void Duty::_p_copy_files(const CopyInformation & items) const {
	std::list< std::pair<std::filesystem::path,std::filesystem::path> > calls;
	for (const auto & i : items.files) {
		calls.emplace_back( fromDir / i,   toDir / i );
	}
	std::for_each(std::execution::par_unseq,
		calls.cbegin(), calls.cend(),
		[](const auto & a) { _p_copy_a_file(a.first,a.second); });
}

inline void Duty::_p_copy_a_file(const std::filesystem::path & a, const std::filesystem::path & b) try {
	if (std::filesystem::exists(b)) {
		std::ifstream varFrom{ a,std::ios::binary };
		std::ifstream varTo{ b,std::ios::binary };

		bool isSame = false;

		if (std::filesystem::file_size(b) == std::filesystem::file_size(a)) {
			constexpr const static int Size = 1024;
			alignas(4) char blockA[Size];
			alignas(4) char blockB[Size];
			std::ifstream varFrom(a, std::ios::binary);
			std::ifstream varTo(b, std::ios::binary);
			do {
				varFrom.read(blockA, Size);
				varTo.read(blockB, Size);

				const auto varNext0 = varFrom.gcount();
				const auto varNext1 = varTo.gcount();

				if (varNext0 != varNext1) {
					break;
				}

				if (varNext0 < 1) {
					isSame = true;
					break;
				}

				if (std::memcmp(blockA, blockB, varNext0) != 0) {
					break;
				}

			} while (varFrom.good());
		}

		if (false == isSame) {
			std::filesystem::copy_file(a, b, std::filesystem::copy_options::overwrite_existing);
		}
	}
	else {
		std::filesystem::copy_file(a, b);
	}
}
catch (...) {
	return;
}
