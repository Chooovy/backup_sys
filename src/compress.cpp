#include "compress.h"

Compress::Compress() {}

Compress::~Compress() {}

Node* Compress::buildHuffmanTreeA(
    const std::unordered_map<unsigned char, ull>& frequency_map) {
    std::priority_queue<Node*, std::vector<Node*>, NodeGreater> pq;
    for (const auto& entry : frequency_map) {
        pq.push(new Node(entry.first, entry.second));
    }

    if (pq.size() == 1) {
        Node* son = pq.top();
        pq.pop();
        Node* parent = new Node('\0', son->frequency);
        parent->left = son;
        pq.push(parent);
    }

    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();  // 更低的在左边
        Node* right = pq.top();
        pq.pop();
        // 选出两个频率最低的节点，成为新节点的左右子节点
        Node* parent = new Node('\0', left->frequency + right->frequency);
        // 每次挑选最低频率的两个节点
        parent->left = left;
        parent->right = right;

        pq.push(parent);
    }
    return pq.top();
}

Node* Compress::buildHuffmanTreeB(
    const std::unordered_map<unsigned char, std::string>& huffman_codes) {
    Node* root = new Node('\0');
    for (const auto& entry : huffman_codes) {
        Node* current = root;
        const std::string& code = entry.second;  // 当前huffman码
        for (char bit : code) {                  // 遍历code的每个bit位
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

void Compress::buildHuffmanCodes(
    Node* root,
    std::string code,
    std::unordered_map<unsigned char, std::string>& huffman_codes) {
    if (root != nullptr && root->left == nullptr &&
        root->right == nullptr) {  // 是叶子节点
        huffman_codes[root->data] = code;
        return;
    }

    if (root != nullptr && root->left != nullptr) {
        buildHuffmanCodes(root->left, code + '0', huffman_codes);
    }

    if (root != nullptr && root->right != nullptr) {
        buildHuffmanCodes(root->right, code + '1', huffman_codes);
    }
}

bool Compress::compressFile(const std::string& input_file,
                            const std::string& output_file) {
    std::ifstream fin(input_file, std::ios::in | std::ios::binary);
    if (!fin) {
        std::cerr << "can not open file:" << input_file << std::endl;
        return false;
    }

    std::unordered_map<unsigned char, ull> frequency_map;  // char有256种
    char ch;                                               // unsigned char
    while (fin.get(ch)) {
        frequency_map[static_cast<unsigned char>(ch)]++;
    }

    std::bitset<8> bits(0);
    unsigned char bit;
    int cnt = 0;

    Node* root = buildHuffmanTreeA(frequency_map);
    std::unordered_map<unsigned char, std::string> huffman_codes;
    buildHuffmanCodes(root, "", huffman_codes);

    /*  file_struct

        size
        originalchar huffmancode
        originalchar huffmancode
        ...
        originalchar huffmancode
        length
        encode_data

    */
    std::ofstream fout(output_file, std::ios::out | std::ios::binary);
    fout << huffman_codes.size() << "\n";
    for (const auto& entry : huffman_codes) {
        fout << entry.first << " " << entry.second << "\n";
    }  // 这段是压缩文件的编码表
    // map设计的不好，太大了，而且以空行分割就读取不了空行

    fin.clear();
    fin.seekg(0, std::ios::beg);
    std::string encode_data;
    while (fin.get(ch)) {
        encode_data += huffman_codes[static_cast<unsigned char>(ch)];
    }  // 将infile中的每一个字符转成huffmancode，然后读入到一行中

    fout << encode_data.length() << '\n';

    /*
    包括文件类型，权值列表，文件长度，以便于从压缩文件中再次生成哈夫曼编码来解压，
    也可以用其他的方式，比如直接将哈夫曼编码以先序遍历的方式写入压缩文件的开始，代码中有体现）
    */

    bits = (0);
    cnt = 0;
    for (char bit : encode_data) {
        if (bit == '1') {
            bits.set(7 - cnt);
        } else {
            bits.reset(7 - cnt);
        }
        if (cnt == 7) {
            char byte = static_cast<char>(bits.to_ulong());
            fout << byte;
            bits.reset();
            cnt = 0;
        } else {
            cnt++;
        }
    }

    if (cnt > 0) {
        char byte = static_cast<char>(bits.to_ulong());
        fout.put(byte);
    }

    fin.close();
    fout.close();

    std::cout << "compress success" << std::endl;
    return true;
}

bool Compress::decompressFile(const std::string& input_file,
                              const std::string& output_file) {
    std::ifstream fin(input_file, std::ios::in | std::ios::binary);
    if (!fin) {
        std::cerr << "can not open the compressed file:" << input_file
                  << std::endl;
        return false;
    }

    // 从文件中读取编码表（huffman_codes）
    std::unordered_map<unsigned char, std::string> huffman_codes;
    char ch;
    std::string code;
    fin.seekg(0, std::ios::beg);

    ull huffmancode_size;
    fin >> huffmancode_size;
    fin.get();

    while (huffmancode_size > 0) {
        fin.get(ch);
        fin >> code;
        huffman_codes[static_cast<unsigned char>(ch)] = code;
        fin.get();
        huffmancode_size--;
    }

    ull datalen;
    fin >> datalen;
    fin.get();

    // 构建 Huffman 树
    Node* root = buildHuffmanTreeB(huffman_codes);

    std::ofstream fout(output_file, std::ios::out);

    std::string encode_data;
    while (fin.get(ch)) {
        encode_data += std::bitset<8>(ch).to_string();
    }

    Node* current = root;
    ull times = 0;
    for (char bit : encode_data) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }
        if (current->left == nullptr && current->right == nullptr) {  // 空指针
            fout.put(current->data);
            current = root;
        }
        if (times == datalen - 1) {
            break;
        } else {
            times++;
        }
    }
    fout.close();
    fin.close();

    std::cout << "decompress success" << std::endl;
    return true;
}