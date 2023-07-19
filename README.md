# Magnus- A UCI Chess Engine

![Chess is everything](https://cdn.discordapp.com/attachments/806974540139200623/1131269149440618516/Quotation-Anatoly-Karpov-Chess-is-everything-art-science-and-sport-60-6-0632.png)

## Table of Contents
- [Universal Chess Interface](#universal-chess-interface)
- [Board Representation](#board-representation)
- [Search Methods](#search-methods)
- [Evaluation](#evaluation)
- [Challenges we faced](#challenges-we-faced)
- [Accomplisments we are proud of](#accomplisments-we-are-proud-of)
- [What we learnt](#what-we-learnt)

## Universal Chess Interface
The Universal Chess Interface (UCI) is a standard protocol for chess engines to communicate with graphical user interfaces (GUIs). It enables platform-independent communication through text commands via standard input and output. The engine waits for commands from the GUI, such as "go" to start calculations, and responds with information like search depth, score, and principal variation using the "info" command. During initialization, the engine provides its identity and available options, allowing the GUI to change parameters using "setoption" commands. UCI streamlines interactions, supporting chess engine analysis, gameplay, and configuration options with ease.

## Board representation
In a UCI chess engine, board representation is a crucial aspect that directly impacts its performance and efficiency. Two popular methods for board representation are Bitboards and Magic Bitboards.

1. Bitboards:
Bitboards are a compact and efficient way to represent the chessboard using a set of 64-bit integers (64 squares on the board). Each bit of the integer represents a square on the chessboard, and a 1 bit at a particular position indicates the presence of a piece on that square, while a 0 bit signifies an empty square. This representation allows for quick and efficient bitwise operations, enabling the engine to perform various calculations such as piece attacks, legal moves generation, and move validation with great speed.

2. Magic Bitboards:
Magic Bitboards are an extension of standard Bitboards and are primarily used for sliding pieces like bishops, rooks, and queens. They utilize magic numbers, precomputed for each square, to determine the attack patterns of sliding pieces in a very efficient manner. By using these magic numbers, the engine can determine all possible attacks of sliding pieces in one or a few bitwise operations, drastically speeding up move generation and evaluation processes. Magic Bitboards significantly reduce the number of operations required to identify valid moves, making them a powerful technique for board representation in UCI chess engines.

Both Bitboards and Magic Bitboards are widely employed in modern chess engines due to their efficiency and speed advantages. They contribute to the engine's overall performance, enabling it to efficiently search for moves, evaluate positions, and play at high levels of play.

## Search Methods
In a UCI chess engine, the search process is a fundamental component responsible for exploring the game tree to find the best move. Several search methods and optimizations are used to make this process efficient and effective:

1. Iterative Deepening:
Iterative Deepening is a technique where the engine performs a series of searches with increasing depth limits. It starts with a shallow search and gradually increases the depth, allowing the engine to exploit the results of the shallower search to improve the deeper searches. This approach helps the engine to explore the most promising variations first and enhances the efficiency of the overall search process.

2. Transposition Table:
The Transposition Table is a cache that stores previously evaluated positions and their corresponding scores. It helps avoid redundant calculations by recognizing positions that have already been encountered during the search. The stored information includes the evaluation score, best move, and search depth, which can be used to speed up the search and improve move ordering.

3. Move Ordering:
Move ordering is critical for efficient searching. It involves evaluating and ordering moves before searching them. Three common move ordering techniques are:

   - Most Valuable Victim/Lesser Valuable Attacker (MVV/LVA):
     MVV/LVA is a move ordering heuristic that prioritizes capturing moves based on the value of the captured piece and the attacking piece. Captures that yield high gains (capturing a higher-valued piece) are searched first, increasing the chances of a cutoff.

   - SEE (Static Exchange Evaluation):
     SEE is used to evaluate the potential outcome of a capture sequence statically, without executing the moves on the board. It helps to prioritize promising captures and avoid fruitless searches.

   - Killer Moves:
     Killer Moves are moves that caused a cutoff in previous iterations of the search. They are kept in a list and searched early in the current iteration. This technique exploits the likelihood that a move that caused a cutoff before might be a good move in the current position as well.

4. Selectivity:
Selectivity techniques aim to reduce the number of nodes searched without sacrificing the quality of the results. Some common selectivity methods include:

   - Null Move Pruning:
     Null Move Pruning involves making an exploratory move by passing the turn to the opponent without performing a real move. If the resulting position is still favorable, it is highly likely that the original position is winning, and this can lead to a significant reduction in search depth, improving efficiency.

   - Check Extensions:
     When searching moves in a check position, Check Extensions extend the search depth to ensure that all possible moves in a check position are thoroughly evaluated.

   - Late Move Reduction (LMR):
     LMR is a technique that reduces the search depth for non-capturing moves that are unlikely to be the best moves. It is an optimization to save search effort on less promising moves and speeds up the search.

   - Quiescence Search:
     Quiescence Search is a specialized extension of the search that continues to search deeper into a position until it reaches a "quiet" or "stable" position, i.e., a position without any immediate captures or checks. This ensures that the engine evaluates positions accurately and avoids the horizon effect.

By combining these search methods and optimizations, UCI chess engines can efficiently explore the game tree, select strong moves, and make strategic decisions at a high level of play.

![Chess is an art of analysis](https://cdn.discordapp.com/attachments/806974540139200623/1131269671132348466/quote-chess-is-the-art-of-analysis-mikhail-botvinnik-60-6-0682.png)
<br/>
## Evaluation
Evaluation in a UCI chess engine is a critical component responsible for assessing the strengths and weaknesses of a given chess position. The evaluation function assigns a numerical score to the position, indicating the engine's assessment of how favorable the position is for the player to move. Several factors are taken into account during the evaluation process:

Material:
Material is the most straightforward and fundamental aspect of chess evaluation. It involves counting the total value of pieces on the board for each side. Different pieces are assigned different values, such as pawns (1 point), knights and bishops (3 points), rooks (5 points), and queens (9 points). The engine aims to have an advantage in material, as it signifies having more powerful pieces and greater control over the board.

Piece Square Table (PST):
The Piece Square Table is an array that assigns specific scores to pieces based on their positions on the board. Each type of piece (pawn, knight, bishop, rook, queen, and king) has its own PST. These scores reflect the strengths and weaknesses of the pieces in various positions on the board. The engine uses PST to favor piece placement that aligns with its strategic goals, such as controlling the center and occupying strong outposts.

Mobility:
Mobility refers to the number of legal moves available to each player. A higher mobility score means that a player has more available moves, which can be advantageous, providing more options and flexibility. The engine takes into consideration the number of legal moves for each side and encourages positions that offer greater mobility.

Pawn Structure:
Pawn structure evaluation involves analyzing the configuration of pawns on the board. Various pawn structures can arise during a game, such as isolated pawns, doubled pawns, backward pawns, and pawn majorities. The engine evaluates the pawn structure's strengths and weaknesses as certain structures can lead to long-term weaknesses or strengths in the position.

Additionally, some UCI chess engines may consider other evaluation factors, such as:

King Safety:
The safety of the kings is crucial, particularly in the middle and endgame. The engine assesses factors like pawn cover in front of the king, the presence of open files around the king's position, and the number of attacking pieces targeting the king. These considerations affect the engine's evaluation as they influence the likelihood of a successful attack or defense.

Development:
The engine may also take into account the development of pieces. In the opening phase, it aims to develop pieces efficiently and avoid unnecessary pawn moves. In the middle game, it might evaluate the activity of the pieces and whether they are fully developed or still on their starting squares.

## Challenges we faced

Developing a UCI chess engine comes with its fair share of challenges, some of which are:

- Search Efficiency: Implementing an efficient search algorithm is crucial for a UCI chess engine to explore the vast number of possible moves within a reasonable time. Achieving a good balance between search depth and speed is challenging, and developers often need to optimize data structures, move generation, and pruning techniques to enhance the search efficiency.

- Evaluation Function: Designing an effective evaluation function is one of the most challenging tasks. The engine's playing strength heavily relies on how accurately it can assess a position. Creating evaluation terms that adequately capture the dynamic aspects of chess and tuning their weights to the right values require extensive testing and fine-tuning.

- Horizon Effect: The horizon effect is a limitation of the search algorithms, where the engine cannot see certain tactical threats or opportunities beyond a fixed depth. This can lead to blunders where the engine misses critical moves just outside its search horizon. Dealing with the horizon effect involves considering quiescence search and extensions to capture tactical nuances.

- Endgame Knowledge: Implementing strong endgame play is challenging because of the complexity of many endgame positions. Without a proper endgame tablebase, the engine may struggle to play endgames optimally. Integrating endgame knowledge into the evaluation and search is a non-trivial task.

- Time Management: Managing the available time during a game effectively is crucial. The engine needs to allocate its time wisely among different phases of the game to avoid time pressure while ensuring deeper calculations in critical positions.

- Hardware Limitations: UCI chess engines can be computationally intensive, especially when running on consumer-grade hardware. Optimizing the engine's performance to run efficiently on various platforms and configurations is a challenge, as developers need to strike a balance between performance and accuracy.

- Testing and Validation: Ensuring the engine's reliability and correctness is challenging due to the sheer number of possible positions and moves in chess. Comprehensive testing, including self-play, tournament-style testing against other engines, and verification of specific tactical and strategic patterns, is essential.

- Human-like Play: Striving to make the engine's play more human-like and less machine-like is an ongoing challenge. Human players often make suboptimal moves to create imbalances and complicate the game, which is difficult for engines that are programmed to play more objectively.

- Adaptability: The chess engine must be adaptable to different playing styles and skill levels. Providing options for users to adjust the engine's strength or playing characteristics to match their preferences can be complex to implement.

## Accomplisments we are proud of

During the development of this UCI chess engine, we have achieved several accomplishments that we are proud of:

- Strong Playing Strength: Through meticulous optimization and fine-tuning of the search algorithms, evaluation function, and other heuristics, our chess engine has achieved a commendable level of playing strength. It can compete with and defeat strong chess players and other well-established chess engines in various settings.

- Efficient Search Algorithms: We have implemented and fine-tuned efficient search algorithms, such as Iterative Deepening, Transposition Table, and Move Ordering techniques. These advancements significantly improved the engine's ability to explore deeper into the game tree within the limited time constraints.

- Robust Evaluation Function: Designing the evaluation function was a challenging task, but we have made significant progress in accurately assessing the dynamic aspects of a chess position. The engine can now better understand imbalances, piece activity, pawn structures, and king safety, leading to more nuanced and human-like play.

- Endgame Knowledge: Integrating endgame knowledge into the engine's evaluation has improved its endgame play substantially. The engine can now navigate complex endgame positions more effectively and reach favorable outcomes in challenging endgame scenarios.

- Horizon Effect Mitigation: While the horizon effect is an inherent limitation in search algorithms, we have implemented extensions and quiescence search techniques to mitigate its impact. As a result, the engine now avoids shallow tactics and demonstrates deeper tactical awareness.

## What we learnt

 Here are some of the key technical lessons that we might have learned during the process:

- Bit Manipulation and Optimization: Chess engines often deal with large sets of data, such as the board state and move generation. Understanding and utilizing bitwise operations and techniques for data optimization, like bitboards and magic bitboards, can significantly boost the engine's performance.

- Algorithmic Efficiency: Writing a high-performing chess engine requires a deep understanding of algorithmic efficiency. Implementing search algorithms like Minimax, Alpha-Beta Pruning, and Iterative Deepening efficiently ensures that the engine explores deeper into the game tree within reasonable time frames.

- Transposition Tables: Learning to implement and utilize a transposition table for storing previously computed positions and their evaluations is crucial for avoiding redundant work and improving search performance.

- Move Generation and Validation: Implementing move generation functions that efficiently generate and validate legal moves is essential. It involves various techniques like sliding piece attacks, move ordering, and quiescence search for capturing moves.

- Evaluation Function Design: Designing an effective evaluation function that accurately assesses the strength of a position involves various factors like material balance, piece-square tables, mobility, pawn structures, king safety, and endgame knowledge.

- Static Exchange Evaluation (SEE): Understanding and implementing the SEE algorithm to evaluate exchanges accurately, especially in quiescence search, contributes to the engine's tactical prowess.

- Efficient Data Structures: Choosing and implementing the right data structures, like arrays, bitsets, and hash tables, can have a significant impact on the engine's memory usage and computational efficiency.

- Parallelization: Utilizing multi-core processors effectively through parallelization techniques like multi-threading (e.g., with the help of the C++11 threading library) can speed up the search process.

- Optimization and Profiling: Profiling the code to identify performance bottlenecks and using optimization techniques, such as loop unrolling and function inlining, can help in achieving a faster and more responsive engine.

- Endgame Algorithms: Learning and implementing specialized endgame algorithms, such as the fifty-move rule, threefold repetition detection, and different endgame tablebases, can significantly improve the engine's play in the endgame phase.

- UCI Protocol and GUI Integration: Understanding the UCI protocol specifications and integrating the engine with various chess GUIs (Graphical User Interfaces) is essential to make the engine accessible and user-friendly.

- Unit Testing and Validation: Implementing thorough unit testing and validation procedures to ensure that changes or optimizations do not introduce bugs or alter the engine's correctness.

- Version Control and Collaboration: Using version control systems like Git and collaborating with other developers through platforms like GitHub facilitates teamwork and code management.

- Error Handling and Robustness: Implementing proper error handling and ensuring the engine behaves gracefully in unexpected situations or invalid input scenarios.