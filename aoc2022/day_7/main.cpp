#include <iostream>
#include <vector>
#include <numeric>

#include "../utils/library.h"

struct FileType {
    enum Types {
        FOLDER,
        FILE
    };

    std::string name;
    int type = FOLDER;
    int size = 0;

    [[nodiscard]] bool isFile() const { return type == FILE; }
};

struct TreeNode {
    FileType type;
    TreeNode* parent = nullptr;
    std::vector<TreeNode*> children;

    [[nodiscard]] bool checkName(const std::string& cmp) const {
        return cmp == type.name;
    }

    [[nodiscard]] bool isFolder() const {
        return type.type == FileType::Types::FOLDER;
    }
};

class FileStructure {
    TreeNode *root = new TreeNode{"/"};



    static TreeNode* up(TreeNode* node) {
        return node->parent;
    }

    std::vector<TreeNode*> smallerThan100k;
public:
    uint64_t maxSize = 70000000;
    uint64_t remainingSpace = maxSize;

    auto parseRow(std::string& terminalRow, TreeNode* currentNode) {
        //std::cout << "Parsing: " << terminalRow << std::endl;

        if (terminalRow.find('$') != std::string::npos) {
            auto command = terminalRow.substr(2, 2);
            if (command == "cd") {
                auto file = terminalRow.substr(5);

                if (file == "/")
                    return root;

                else if (file == "..")
                    return up(currentNode);

                else {
                    for (auto& child : currentNode->children) {
                        if (child->checkName(file)) {
                            return child;
                        }
                    }
                }
            } else {
                return currentNode;
            }
        }

        auto [fileSize, fileName] = splitString(terminalRow, ' ');

        TreeNode* newNode = nullptr;

        if (fileSize == "dir") {
            newNode = new TreeNode{
                    {fileName},
                    currentNode
            };
        } else {
            newNode = new TreeNode{
                    {fileName, FileType::Types::FILE, std::stoi(fileSize)},
                    currentNode
            };

            auto *temp = newNode->parent;

            while (temp != nullptr) {
                temp->type.size += newNode->type.size;
                temp = temp->parent;
            }
        }

        currentNode->children.push_back(newNode);

        return currentNode;
    }

    auto getRoot() {
        return root;
    }

    void print(const std::string& prefix, const TreeNode* node, bool isEnd) {
        if( node == nullptr ) return;

        std::cout << prefix;
        auto size = std::to_string(node->type.size);


        // printTree the value of the node
        std::cout << (node->isFolder() ? "(" + node->type.name + ") : " + size  : node->type.name) << std::endl;


        for (int i = 0; i < node->children.size(); i++) {
            if (i == node->children.size()-1)
                print( prefix+ "     ", node->children[i], true);
            else
                print( prefix + "     ", node->children[i], false);
        }
    }

    void populateSmallerThan100k(TreeNode* node) {
        if (node->isFolder() && node->type.size <= 100000)
            smallerThan100k.push_back(node);

        for (auto& child : node->children) {
            populateSmallerThan100k(child);
        }
    }

    [[nodiscard]] size_t numberOfSmallDirectories() const {
        return smallerThan100k.size();
    }

    [[nodiscard]] auto sizeOfSmallDirectories() const {
        return std::accumulate(smallerThan100k.begin(), smallerThan100k.end(), 0, [&](int a, const TreeNode* b){ return a + b->type.size; });
    }

    void checkChildren(TreeNode* node, std::pair<std::string, uint64_t>& validDeletion) {
        if (!node->isFolder() || node->type.size < 30000000-remainingSpace)
            return;

        if (node->type.size < validDeletion.second) {
            validDeletion = std::pair(node->type.name, node->type.size);
        }

        for (auto& child : node->children)
            checkChildren(child, validDeletion);
    }

    auto findSmallestSingleDirectoryToDelete() {
        remainingSpace -= root->type.size;
        std::pair<std::string, uint64_t> validDeletion(root->type.name, root->type.size);

        checkChildren(root, validDeletion);

        return validDeletion;
    }

};

int main() {
    auto input = readInputToStringVector("input.txt");

    FileStructure fileStructure;

    auto currentNode = fileStructure.getRoot();
    for (auto & line : input) {
        currentNode = fileStructure.parseRow(line, currentNode);
    }

    //fileStructure.print("", fileStructure.getRoot(), true);

    fileStructure.populateSmallerThan100k(fileStructure.getRoot());

    std::cout << "Size of entire system: " << fileStructure.getRoot()->type.size << std::endl;
    std::cout << "Number of dir with 10000 or less: " << fileStructure.numberOfSmallDirectories() << std::endl;
    std::cout << "Size of dir with 10000 or less: " << fileStructure.sizeOfSmallDirectories() << std::endl;

    auto [dirName, dirSize] = fileStructure.findSmallestSingleDirectoryToDelete();

    std::cout << "Remaining space " << fileStructure.remainingSpace << std::endl;

    std::cout << "Smallest directory to delete that will fit: " << dirName << " : " << dirSize << std::endl;

    return 0;
}
