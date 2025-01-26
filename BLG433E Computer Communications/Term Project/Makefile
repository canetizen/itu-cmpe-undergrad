.PHONY: all run-server run-client clean

PYTHON = python3.12
SLEEP = sleep 5
TERMINAL = gnome-terminal --
TEXTFILE = rules.txt

# [1, 5, 10, 20]
SELECTED_ERROR_RATE = 1

# [1, 10, 50, 100]
SELECTED_WIN_SIZE = 100

all: run-server
	$(SLEEP)
	@make run-client

run-server:
	@$(TERMINAL) bash -c "$(PYTHON) src/server.py $(SELECTED_WIN_SIZE) $(SELECTED_ERROR_RATE); exec bash" & echo "Server started in new terminal" &

run-client:
	@$(TERMINAL) bash -c "$(PYTHON) src/client.py $(SELECTED_WIN_SIZE) $(SELECTED_ERROR_RATE) $(TEXTFILE); exec bash" & echo "Client started in new terminal" &

stop:
	@pkill -f "$(PYTHON) src/server.py" || true
	@pkill -f "$(PYTHON) src/client.py" || true
	@echo "Stopped all processes"

