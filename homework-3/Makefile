.PHONY: build clean run

build:
	@mkdir -p build
	@cd build && cmake .. && make -j$$(nproc)

run: build
	@./build/homework-3

clean:
	@rm -rf build

rebuild: clean build