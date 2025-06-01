#!/bin/bash

# Basit test fonksiyonu:
# 1. Komutu çalıştırır
# 2. Çıktıyı beklenenle karşılaştırır
# 3. Sonuca göre DOĞRU/YANLIŞ yazdırır
run_test() {
    description="$1"
    command="$2"
    expected="$3"

    # Komutu çalıştır, stdout al (stderr’yi de eklemek istersen '2>&1' ekle)
    output=$(eval "$command")

    if [ "$output" == "$expected" ]; then
        echo "✅ $description → DOĞRU"
    else
        echo "❌ $description → YANLIŞ"
        echo "   Beklenen: [$expected]"
        echo "   Alınan:   [$output]"
    fi
}

echo "==== TEK TIRNAK TESTLERİ ===="

run_test "Tek tırnak: basit literal" \
    "echo 'merhaba dünya'" \
    "merhaba dünya"

run_test "Tek tırnak: değişken genişlemez" \
    "USER=deneme; echo 'merhaba \$USER'" \
    "merhaba \$USER"

run_test "Tek tırnak: komut genişlemez" \
    "echo 'bugün tarih: \$(date)'" \
    "bugün tarih: \$(date)"

run_test "Tek tırnak: literal kaçış karakterleri" \
    "echo 'merhaba \\n \\t \\r'" \
    "merhaba \\n \\t \\r"

run_test "Tek tırnak: özel karakterler" \
    "echo '|&><;*?!{}[]'" \
    "|&><;*?!{}[]"

run_test "Tek tırnak: içte tek tırnak (kaçırarak)" \
    "echo 'merhaba '\''içte tek tırnak'\'' bitti'" \
    "merhaba 'içte tek tırnak' bitti"

run_test "Tek tırnak: sadece boş" \
    "echo ''" \
    ""

echo "==== ÇİFT TIRNAK TESTLERİ ===="

run_test "Çift tırnak: basit literal" \
    'echo "merhaba dünya"' \
    "merhaba dünya"

run_test "Çift tırnak: değişken genişler" \
    'USER=deneme; echo "merhaba $USER"' \
    "merhaba deneme"

run_test "Çift tırnak: komut genişler" \
    'echo "bugün tarih: $(echo 2025-06-01)"' \
    "bugün tarih: 2025-06-01"

run_test "Çift tırnak: kaçışlı \$" \
    'echo "para işareti: \$100"' \
    "para işareti: \$100"

run_test "Çift tırnak: backslash" \
    'echo "merhaba \\ dünya"' \
    "merhaba \\ dünya"

run_test "Çift tırnak: içte tek tırnak" \
    'echo "bu '\''tek tırnak'\'' içerir"' \
    "bu 'tek tırnak' içerir"

run_test "Çift tırnak: özel karakterler" \
    'echo "|&><;*?!{}[]"' \
    "|&><;*?!{}[]"

run_test "Çift tırnak: sadece boş" \
    'echo ""' \
    ""

echo "==== KARMA TESTLER ===="

run_test "Karma: çift içinde tek tırnak" \
    'echo "tek: '\'' çift: \""' \
    "tek: ' çift: \""

run_test "Karma: tek içinde çift tırnak (kaçırarak)" \
    'echo '\''çift: "\"\''' \
    'çift: "'

echo "==== TESTLER BİTTİ ===="
