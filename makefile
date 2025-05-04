CXX = g++
CXXFLAGS = -std=c++23 -O3
MKLFLAGS = -I include -I $$MKLROOT/include -L $$MKLROOT/lib -lmkl_rt -lpthread -lm

# ディレクトリ
SRC_DIR = src
OUTPUT_DIR = bin

# デフォルト値
SRC = test.cpp
OUT = a.out

# デフォルトターゲット
all: compile run

# コンパイルのみ
compile:
	@mkdir -p $(dir $(OUT))
	$(CXX) $(SRC_DIR)/$(SRC) $(CXXFLAGS) $(MKLFLAGS) -o $(OUTPUT_DIR)/$(OUT)

# 実行ファイルを実行
run: 
	./$(OUTPUT_DIR)/$(OUT)

# ヘルプ
help:
	@echo "使い方:"
	@echo "  make compile SRC=<ソースファイル> OUT=<出力ファイル>  # コンパイルのみ"
	@echo "  make run SRC=<ソースファイル> OUT=<出力ファイル>      # コンパイルして実行"
