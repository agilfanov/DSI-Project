NUM_TARGET_MODELS=2

cmake --build cmake-build-debug --clean-first
mpirun -np $((NUM_TARGET_MODELS + 2)) ./cmake-build-debug/DSI-Project
