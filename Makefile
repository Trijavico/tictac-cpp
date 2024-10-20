
run: build
	@./bin/main

build: ensure_bin
	@g++ main.cpp -o ./bin/main

ensure_bin:
	@mkdir -p ./bin
