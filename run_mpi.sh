NUM_TARGET_MODELS=2

DRAFTER_GGUF_PATH=
TARGET_GGUF_PATH=


cmake --build cmake-build-debug --clean-first
mpirun -np $((NUM_TARGET_MODELS + 2)) ./cmake-build-debug/DSI-Project "$DRAFTER_GGUF_PATH" "$TARGET_GGUF_PATH"
