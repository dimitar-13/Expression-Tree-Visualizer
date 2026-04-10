# Expression-Tree-Visualizer

## Initial description
 The project will represent a application that should have these main functionality:
 - A user can pass a expression in the form of `2*3 + 10 - 2/3`
 - The application will take that expression and will represent it in form of a tree
 - The user can go forward and backwards of each step of the generating algorithm using buttons
 - Using diff buttons `Show forward order` and `Show reverse order` can a interactive animation showing how both forms of the expression are generated
 - The user can enter new expression and using a button `Generate expression` will erase the current one and start a new one

 ## What we need for the project
 - Window handling library like `glfw`
 - Library for exposing `OpenGL` calls like `Glew` or `Glut`
 - UI library for the user to interact wit the application maybe `ImGui`
 - Shaders for drawing the tree elements: Circle/Node, line/connection, number/symbol for each node
 - Logic for generating the tree itslef
 - Logic for undo-redo action
 - Logic for finding the forward and reverse order expressions

 ## Generating tree algorythm
 We recive a expression like `2 + 4 - 6`(for this explenation we asume is a valid expression) so we do:
 - Each number becomes a letter from a-z
 - Each symbol will have a prioraty where: () > ^ > *,/ > +,-
 - We read the whole expression from left to right and find the highest prioraty symbol, and construct the node using the letters, example: a ^ c, we have `a` and `c` connected with ^
 - Since we read left to right, we fix the problem if we encoutner symbols with simular priorary, in that case the left one is first
 - After we create a new node like example above we asing that part to a new variable and continue untill we finish
 Example how this may look:

 `4 + 6 * 5` -> `a + b * c` -> `a + d` -> `e`

 ## Representing nodes
 A idea is that each node will be represented by the following struct below:
 ```c++
struct Node
{
    char node_symbol; // this can be anything from a-z but also /,*,+,- etc.
    Node* left_node;
    Node* right_node;
}

 ```
 That way as we create the nodes(we will always start from bottom nodes) we will create the parent nodes and set their left and right nodes. When we finish the tree we should def keep a ref to the top node.


 ## Undo-Redo logic
 As we generate the tree we can use a List(or reffered as linked list). That way we can keep in it some state information about the tree once again in a struct as we generate. When the user wants to go back and forward he can just go to next element of linked list.
 A example data for this state struct can be:
 ```c++
struct GenerationState
{
    string current_expression; // This will keep a string that will be the way current expression looks like
    std::vector<Node> nodes; // For now it will be like this, maybe not the best idea to keep the whole node list in every state
}
 ```

 ## Plan of the project
 Because this logic doesnt relly on UI we will first start by implementing the tree generting logic and undo-redo logic healdessly(without UI)
 
 For this stage of project is enought