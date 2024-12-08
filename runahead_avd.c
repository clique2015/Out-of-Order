  // Function to simulate instruction execution using Runahead and AVD prediction
    void execute_instructions_with_avd_prediction(std::vector<int>& instructions, AVD_Predictor& avd_predictor) {
        // Simulate instruction window size (for runahead execution)
        const int instruction_window_size = 10;
        for (int instruction : instructions) {
            std::cout << "Processing instruction at address: " << instruction << std::endl;
            // Try to load the value from cache first
            int result = load_from_cache(instruction);
            if (result == -1) {  // Cache miss
                std::cout << "Cache miss for address: " << instruction << std::endl;
                // Predict the value using AVD predictor (if available)
                int predicted_value = avd_predictor.predict_value(instruction);
                if (predicted_value != -1) {
                    std::cout << "AVD Prediction: Predicted value for address " << instruction << " is " << predicted_value << std::endl;
                    // Speculatively execute the dependent load instruction (if any)
                    // Here, we assume the predicted value is used for the next load
                    // In a real applications, more instructions would depend on this prediction.
                }
                // Simulate fetching the value from memory after a cache miss
                int fetched_data = load_from_memory(instruction);
                std::cout << "Fetched data for address " << instruction << ": " << fetched_data << std::endl;
                // Update the AVD predictor with the new instruction(we assume there is a predictor register)
                avd_predictor.update(instruction, fetched_data);
                if (predicted_value == -1) { // Simulate entering runahead mode
                    std::cout << "Entering runahead mode..." << std::endl;
                    // Pre-execute the next instructions 
                    for (int i = 0; i < instruction_window_size; ++i) {
                        int next_instruction = instructions[instruction + i];
                        // Simulate speculative execution
                        std::cout << "Speculatively executing instruction " << next_instruction << std::endl;                        
                        // Check if any of the pre-executed instructions cause cache misses themselves
                        int prefetch_result = load_from_cache(next_instruction);
                        if (prefetch_result == -1) {// If another cache miss occurs, simulate memory fetch
                            std::cout << "Cache miss during runahead execution, fetching from memory." << std::endl;
                            load_from_memory(next_instruction);
                        }
                    }  
                    // Simulate memory latency 
                    int fetched_data = load_from_memory(instruction);  // Resolve the original cache miss
                    std::cout << "Fetched data for address " << instruction << ": " << fetched_data << std::endl;
                }            
            } else {// Cache hit: No prediction needed
                std::cout << "Cache hit for address: " << instruction << " with value " << result << std::endl;
            }
        }
    }
