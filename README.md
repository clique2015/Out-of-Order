# Out-of-Order


\section*{Instruction Execution with Runahead and AVD Prediction}

\textbf{Instruction Simulation:} The function \texttt{execute\_instructions\_with\_avd\_prediction} processes a list of instructions, simulating how an out-of-order processor might execute them.

\textbf{Cache Lookup:} For each instruction, the system first tries to load the value from the cache by calling \texttt{load\_from\_cache(instruction)}. If there is a cache miss (indicated by a return value of -1), the system tries to predict the value of the instruction using the AVD Predictor.

\textbf{AVD Prediction:} If the AVD predictor is available and can make a prediction, it predicts the value of the instruction that caused the cache miss. The predicted value is printed, and the processor speculatively executes any dependent instructions using the predicted value.

\textbf{Memory Fetch:} Whether the prediction is made or not, the processor simulates fetching the value from memory after the cache miss by calling \texttt{load\_from\_memory(instruction)} and updates the AVD predictor with the fetched data.

\textbf{Entering Runahead Mode:} If the AVD prediction fails (i.e., no prediction is available), the system enters \textit{runahead mode}. In this mode, the processor speculatively executes the next \texttt{instruction\_window\_size} instructions, ignoring any cache misses that may occur during this speculative execution. These instructions are executed in parallel without waiting for the resolution of the current cache miss.

\textbf{Handling Cache Misses During Runahead:} While executing in runahead mode, if a cache miss occurs for any instruction, the system fetches data from memory for that instruction, simulating the delay caused by memory latency.

\textbf{Final Memory Fetch:} After completing runahead execution, the processor fetches the original instruction's data from memory to resolve the cache miss.
