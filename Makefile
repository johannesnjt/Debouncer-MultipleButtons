CC := g++
CFLAGS := -Werror -D DEVENV

MODULE_BSP = BSP
MODULE_DEBOUNCER = debouncer
UNITY = unity
TEST_EXE := test

LIB_DIR := lib
TEST_DIR := test
BUILD_DIR := build

INCLUDES := $(LIB_DIR)/$(MODULE_BSP) $(LIB_DIR)/$(MODULE_DEBOUNCER) $(LIB_DIR)/$(UNITY) $(TEST_DIR)/$(MODULE_DEBOUNCER)
INCLUDES := $(addprefix -I./, $(INCLUDES:%/=%))

OBJECTS := $(notdir $(wildcard $(LIB_DIR)/$(MODULE_DEBOUNCER)/*.cpp) $(wildcard $(TEST_DIR)/$(MODULE_DEBOUNCER)/*.cpp) $(wildcard $(LIB_DIR)/$(UNITY)/*.cpp)) 
OBJECTS := $(addprefix $(BUILD_DIR)/, $(OBJECTS:.cpp=.o))

all: .mkbuild $(BUILD_DIR)/$(TEST_EXE)
	@echo ""
	@echo "************ The Targets ************"
	@echo "** clean: to clean"
	@echo "** check: to run the test"
	@echo "*************************************"
	@echo ""

$(BUILD_DIR)/$(TEST_EXE): $(OBJECTS)
	$(CC) $^ -coverage -o $@

$(BUILD_DIR)/%.o: $(LIB_DIR)/$(MODULE_DEBOUNCER)/%.cpp
	$(CC) -MMD $(CFLAGS) --coverage -o $@ $(INCLUDES) -c $<

$(BUILD_DIR)/%.o: $(LIB_DIR)/$(UNITY)/%.cpp
	$(CC) -MMD $(CFLAGS) --coverage -o $@ $(INCLUDES) -c $<

$(BUILD_DIR)/%.o : $(TEST_DIR)/$(MODULE_DEBOUNCER)/%.cpp
	$(CC) -MMD $(CFLAGS) -o $@ $(INCLUDES) -c $<

check: .mkbuild $(BUILD_DIR)/$(TEST_EXE)
	@echo ""
	@echo "**************************************"
	@echo "********** Run The Test **************"
	@echo "**************************************"
	@echo ""
	@./$(BUILD_DIR)/$(TEST_EXE); \
	gcovr -r . --html-details -o $(BUILD_DIR)/index.html

# Include automatically generated dependencies
-include $(OBJECTS:.o=.d)

.PHONY: clean .mkbuild check all

clean:
	@rm -rf $(BUILD_DIR)

.mkbuild:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/HTML