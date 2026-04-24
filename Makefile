CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2
TARGET = scheduler

SRC = main.c \
      Queue.c \
      Priority_queue.c \
      utils.c \
      Scheduling_Algorithms/PRIORITYPRE.c \
      Scheduling_Algorithms/PRIOTITY_NONPRE.c \
      Scheduling_Algorithms/miltilevel_queue.c \
      Scheduling_Algorithms/FCFS.c \
      Scheduling_Algorithms/ROUND_ROBIN.c \
      Scheduling_Algorithms/SJF.c \
      Scheduling_Algorithms/SRTF.c

OBJ = $(SRC:.c=.o)

# Default target
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile each .c into .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean ONLY object files (keep executable)
clean:
	rm -f $(OBJ)

# Clean everything (object files + executable)
distclean:
	rm -f $(OBJ) $(TARGET)

# Rebuild from scratch (clean everything then build)
re: distclean all
