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
        Node* left = pq.top(); pq.pop();//���͵������
        Node* right = pq.top(); pq.pop();
        //ѡ������Ƶ����͵Ľڵ㣬��Ϊ�½ڵ�������ӽڵ�
        Node* parent = new Node('\0', left->frequency + right->frequency);
        //ÿ����ѡ���Ƶ�ʵ������ڵ�
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
        const std::string& code = entry.second;//��ǰhuffman��
        for (char bit : code) {//����code��ÿ��bitλ
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
    if (root !=nullptr && root->left == nullptr && root->right == nullptr) {//��Ҷ�ӽڵ�
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

    std::unordered_map<unsigned char, ull> frequencyMap;//char��256��
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
    }//�����ѹ���ļ��ı����
    //map��ƵĲ��ã�̫���ˣ������Կ��зָ�Ͷ�ȡ���˿���

    inFile.clear();
    inFile.seekg(0, std::ios::beg);
    std::string encodedData;
    while (inFile.get(ch)) {
        encodedData += huffmanCodes[static_cast<unsigned char>(ch)];
    }//��infile�е�ÿһ���ַ�ת��huffmancode��Ȼ����뵽һ����
    


    outFile << encodedData.length() << '\n';

    /*
    �����ļ����ͣ�Ȩֵ�б��ļ����ȣ��Ա��ڴ�ѹ���ļ����ٴ����ɹ�������������ѹ��
    Ҳ�����������ķ�ʽ������ֱ�ӽ���������������������ķ�ʽд��ѹ���ļ��Ŀ�ʼ�������������֣�
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

    // ���ļ��ж�ȡ�����huffmanCodes��
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

    // ���� Huffman ��
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
        if (current->left == nullptr && current->right == nullptr) {//��ָ��
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