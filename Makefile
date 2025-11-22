CC := gcc
CFLAGS := -Wall -Wextra -O2
BUILD_DIR := build
TARGET := ftp_client
SRC_DIR := src
SRCS := $(SRC_DIR)/ftp_client.c $(SRC_DIR)/ftp_url.c
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