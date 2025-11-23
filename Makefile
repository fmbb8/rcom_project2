
SERVER = speedtest.tele2.net
DEFAULT_PATH = 1MB.zip

# Example combined default URL
DEFAULT_URL = ftp://$(SERVER)/$(DEFAULT_PATH)

CC := gcc
CFLAGS := -Wall -Wextra -O2
BUILD_DIR := build
TARGET := ftp_client
SRC_DIR := src
SRCS := $(SRC_DIR)/ftp_client.c $(SRC_DIR)/ftp_url.c $(SRC_DIR)/ftp_resolver.c
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))


.PHONY: all clean run dirs
all: dirs $(BUILD_DIR)/$(TARGET)


dirs:
	@mkdir -p $(BUILD_DIR)


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | dirs
	$(CC) $(CFLAGS) -c $< -o $@


$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
	@echo "Built $(BUILD_DIR)/$(TARGET)"

clean:
	rm -rf $(BUILD_DIR)
	@echo "Cleaned build/"

run: all
	@if [ -z "$(ARGS)" ]; then \
	    FP="$(FILE_PATH)"; \
	    if [ -z "$$FP" ]; then FP="$(DEFAULT_PATH)"; fi; \
	    URL="ftp://$(SERVER)/$$FP"; \
	else \
	    URL="$(ARGS)"; \
	fi; \
	echo "Running with URL: $$URL"; \
	./$(BUILD_DIR)/$(TARGET) $$URL