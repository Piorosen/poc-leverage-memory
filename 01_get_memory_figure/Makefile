
.PHONY: install_cmake
install_cmake:
	wget https://github.com/Kitware/CMake/releases/download/v3.29.5/cmake-3.29.5-linux-aarch64.tar.gz && \
	tar -zxvf cmake-3.29.5-linux-aarch64.tar.gz && \
	cd ./cmake-3.29.5-linux-aarch64 && \
	sudo cp -r . /usr/ && \
	cd .. && \
	rm -rf cmake-3.29.5-linux-aarch64/ cmake-3.29.5-linux-aarch64.tar.gz


release:
	