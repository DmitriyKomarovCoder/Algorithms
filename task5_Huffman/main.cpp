#include "Haffman.hpp"
#include "Test.hpp"

/*
Encode
+1. Один раз проходимся по входным данным, считая частотности букв алфавита. Так как пройтись придется дважды, надо запомнить весь ввод. +
+2. Для всех букв с ненулевой частотностью создаем узел дерева Хаффмана, где храним частотность, букву, указатели на левого и правого потомков. Кладем каждый узел в очередь с приоритетом (min Heap по частотности). +
+3. Пока в куче более одного элемента, достаем из нее по 2 узла на каждой итерации. Создаем новый узел, к которому правым и левым дочерним элементом цепляем извлеченные только что узлы, а в частотность пишем сумму их частотностей. Кладем этот новый узел в кучу. Когда в куче останется один элемент -- это корень построенного дерева Хаффмана.
+4. Строим по дереву Хаффмана таблицу кодов, где каждому кодируемому символу алфавита ставится в соответствие вектор битов -- его код. Для этого обходим дерево в глубину, попутно тащим за собой вектор пути (пошли направо -- добавляем 1, пошли налево -- 0), как только дошли до листа -- пишем в таблицу символ и битовый путь к нему.
5. Чтобы впоследствии раскодировать данные, понадобится в самом сообщении передать построенное дерево. Можно сделать это так:
  5.1 Пишем байт с числом символов алфавита.
  5.2. В корне дерева Хаффмана начинаем алгоритм:
    Текущий узел лист? Пишем бит "1" и байт с символом алфавита.
    Текущий узел внутренний? Рекурсивно вызываем эту функцию для левого поддерева, для правого поддерева, затем пишем бит "0"
6. Кодируем исходное сообщение при помощи таблицы. Смотрим код для очередного символа -- пишем его побитово. Чтобы знать, сколько в последнем байте закодированного сообщения значащих бит, надо как-то передать это. Можно это записать в самом последнем байте вывода, после закодированного сообщения. Можно посчитать заранее (у нас есть частотность каждого символа и длина его кода), записать после 5.1 или вообще самым первым байтом вывода. Вариантов масса. Главное, не забыть.

Decode
1. Читаем дерево
  1.1. Читаем байт с числом букв алфавита.
  1.2. Начинаем читать само дерево. Нам понадобится стек. Алгоритм:
  Пока не прочитали столько букв, сколько их в кодируемом алфавите, и пока в стеке более одного узла, читаем бит.
    Прочитали 1? Читаем еще байт, там символ кодируемого алфавита. Создаем узел дерева Хаффмана с этим символом, кладем узел в стек.
    Прочитали 0? Достаем из стека два узла, создаем новый, к которому цепляем извлеченные узлы (первый извлеченный -- правый потомок, второй -- левый). Кладем новый узел в стек.
  Мы восстановили дерево Хаффмана.
3. Теперь идет закодированная последовательность. Читаем побитово, обходим дерево Хаффмана от корня к листьям (прочитали 1 -- идем вправо, 0 -- влево). Дошли до листа -- декодировали очередной символ, пишем его. Не забываем вовремя остановиться, последний байт кодовой последовательности может содержать мусорные биты.
*/

void Encode(IInputStream& original, IOutputStream& compressed) {
    std::unordered_map<byte, int> fTable;
    byte value;
    std::vector<byte> buffer;
    while (original.Read(value)) {
        fTable[value]++;
        buffer.push_back(value);
    }

    // строим дерево Хаффмана

    Haffman haffman;
    haffman.buildTree(fTable);
    // Строим таблицу кодов
    std::vector<bool> code;
    haffman.buildTable(code);

    // Записываем в compressed размер алфавита
    compressed.Write((byte)(fTable.size()));

    // Записываем в compressed дерево
    BitWriter writer;
    haffman.Serialize(writer);
    auto treeData = writer.GetBuffer();
    for (auto date : treeData) {
        compressed.Write(date);
    }

    // Записываем закодированные данные в compressed
    writer = BitWriter();
    for (byte symbol : buffer) {
        haffman.encode(symbol, writer);
    }

    // Записываем кол-во бит в последнем байте
    size_t bitCount = writer.GetBitCount();
    if (bitCount & 8 != 0) {
        byte lastByteBitsCount = 8 - static_cast<byte>(bitCount & 8);
        writer.WriteByte(lastByteBitsCount);
    } else {
        writer.WriteByte(0);
    }

    const std::vector<unsigned char>& encodedData = writer.GetBuffer();
    for (auto date : encodedData) {
        compressed.Write(date);
    }
}

// void Decode(IInputStream& compressed, IOutputStream& original) {
//     byte size;
//     compressed.Read(size);

//     Haffman haffman;
//     haffman.

// }

int main() {
    return 0;
}