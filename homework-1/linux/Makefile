.PHONY: build clean run

build:
	@mkdir -p build
	@cd build && cmake .. && make -j$$(nproc)

run: build
	@./build/Main/Main

clean:
	@rm -rf build

rebuild: clean build