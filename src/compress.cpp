#include "compress.h"

// Compress::Compress(std::string inputFile_, std::string compressedFile_, std::string outputFile_) {
//     std::string inputFile = inputFile_
//     std::string compressedFile = compressedFile_;
//     std::string outputFile = outputFile_;
// }

Compress::Compress() {

}

Compress::~Compress() {

}

Node* Compress::buildHuffmanTree_a(const std::unordered_map<unsigned char, ull>& frequencyMap) {
    std::priority_queue<Node*, std::vector<Node*>, CompareNodes> pq;
    for (const auto& entry : frequencyMap) {
        pq.push(new Node(entry.first, entry.second));
    }

    if (pq.size() == 1) {
        Node* son = pq.top(); pq.pop();
        Node* parent = new Node('\0', son->frequency);
        parent->left = son;
        pq.push(parent);
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();//更低的在左边
        Node* right = pq.top(); pq.pop();
        //选出两个频率最低的节点，成为新节点的左右子节点
        Node* parent = new Node('\0', left->frequency + right->frequency);
        //每次挑选最低频率的两个节点
        parent->left = left;
        parent->right = right;

        pq.push(parent);
    }
    return pq.top();
}

Node* Compress::buildHuffmanTree_b(const std::unordered_map<unsigned char, std::string>& huffmanCodes) {
    Node* root = new Node('\0');
    for (const auto& entry : huffmanCodes) {
        Node* current = root;
        const std::string& code = entry.second;//当前huffman码
        for (char bit : code) {//遍历code的每个bit位
            if (bit == '0') {
                if (current->left == nullptr) {
                    current->left = new Node('\0');
                }
                current = current->left;
            } else {
                if (current->right == nullptr) {
                    current->right = new Node('\0');
                }
                current = current->right;
            }
        }
        current->data = entry.first;
    }
    return root;
}

void Compress::buildHuffmanCodes(Node* root, std::string code, std::unordered_map<unsigned char, std::string>& huffmanCodes) {
    if (root !=nullptr && root->left == nullptr && root->right == nullptr) {//是叶子节点
        huffmanCodes[root->data] = code;
        return;
    }

    if (root !=nullptr && root->left != nullptr) {
        buildHuffmanCodes(root->left, code + '0', huffmanCodes);
    }

    if (root !=nullptr && root->right != nullptr) {
        buildHuffmanCodes(root->right, code + '1', huffmanCodes);
    }
}


bool Compress::compressFile(const std::string& inputFile, const std::string& compressedFile) {
    std::ifstream inFile(inputFile, std::ios::in | std::ios::binary);
    if (!inFile) {
        std::cerr << "can not open file:" << inputFile << std::endl;
        return false;
    }

    std::unordered_map<unsigned char, ull> frequencyMap;//char有256种
    char ch;//unsigned char
    while (inFile.get(ch)) {
        frequencyMap[static_cast<unsigned char>(ch)]++;
    }

    std::bitset<8> bits(0);
    unsigned char bit;
    int cnt = 0;

    Node* root = buildHuffmanTree_a(frequencyMap);
    std::unordered_map<unsigned char, std::string> huffmanCodes;
    buildHuffmanCodes(root, "", huffmanCodes);

/*  file_struct

    size
    originalchar huffmancode
    originalchar huffmancode
    ...
    originalchar huffmancode
    length
    encodedData

*/
    std::ofstream outFile(compressedFile, std::ios::out | std::ios::binary);
    outFile << huffmanCodes.size() << "\n";
    for (const auto& entry : huffmanCodes) {
        outFile << entry.first << " " << entry.second << "\n";
    }//这段是压缩文件的编码表
    //map设计的不好，太大了，而且以空行分割就读取不了空行

    inFile.clear();
    inFile.seekg(0, std::ios::beg);
    std::string encodedData;
    while (inFile.get(ch)) {
        encodedData += huffmanCodes[static_cast<unsigned char>(ch)];
    }//将infile中的每一个字符转成huffmancode，然后读入到一行中
    


    outFile << encodedData.length() << '\n';

    /*
    包括文件类型，权值列表，文件长度，以便于从压缩文件中再次生成哈夫曼编码来解压，
    也可以用其他的方式，比如直接将哈夫曼编码以先序遍历的方式写入压缩文件的开始，代码中有体现）
    */

    bits = (0);
    cnt = 0;
    for (char bit : encodedData) {
        if (bit == '1') {
            bits.set(7-cnt);
        }
        else {
            bits.reset(7-cnt);
        }
        if (cnt == 7) {
            char byte = static_cast<char>(bits.to_ulong());
            outFile << byte;
            bits.reset();
            cnt = 0;
        }
        else {
            cnt++;
        }
    }

    if (cnt > 0) {
        char byte = static_cast<char>(bits.to_ulong());
        outFile.put(byte);
    }

    inFile.close();
    outFile.close();

    std::cout << "compress success" << std::endl;
    return true;
}

bool Compress::decompressFile(const std::string& compressedFile, const std::string& outputFile) {
    std::ifstream inFile(compressedFile, std::ios::in | std::ios::binary);
    if (!inFile) {
        std::cerr << "can not open the compressed file:" << compressedFile << std::endl;
        return false;
    }

    // 从文件中读取编码表（huffmanCodes）
    std::unordered_map<unsigned char, std::string> huffmanCodes;
    char ch;
    std::string code;
    inFile.seekg(0, std::ios::beg);

    ull huffmancode_size;
    inFile >> huffmancode_size;
    inFile.get();

    while (huffmancode_size > 0) {
        inFile.get(ch);
        inFile >> code;
        huffmanCodes[static_cast<unsigned char>(ch)] = code;
        inFile.get();
        huffmancode_size--;
    }

    ull datalen;
    inFile >> datalen;
    inFile.get();

    // 构建 Huffman 树
    Node* root = buildHuffmanTree_b(huffmanCodes);

    std::ofstream outFile(outputFile, std::ios::out);

    std::string encodedData;
    while (inFile.get(ch)) {
        encodedData += std::bitset<8>(ch).to_string();
    }

    Node* current = root;
    ull times = 0;
    for (char bit : encodedData) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }
        if (current->left == nullptr && current->right == nullptr) {//空指针
            outFile.put(current->data);
            current = root;
        }
        if(times == datalen - 1){
            break;
        }
        else{
            times++;
        }
    }
    outFile.close();
    inFile.close();

    std::cout << "decompress success" << std::endl;
    return true;
}