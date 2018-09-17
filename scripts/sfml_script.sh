brew install sfml
cp -r ~/.brew/Cellar/sfml/2.4.2_1/include/SFML ./includes
export LD_LIBRARY_PATH=~/.brew/Cellar/sfml/2.4.2_1/lib
echo "export LD_LIBRARY_PATH=~/.brew/Cellar/sfml/2.4.2_1/lib" >> ~/.zshrc