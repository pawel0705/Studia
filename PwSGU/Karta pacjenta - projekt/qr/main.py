# nie jestem pewien co do tych poleceń pip, dużo instalowałem/testowałem, nie pamiętam co do czego było
# pip install qrcode
def generate_qr(num_to_gen):
    """
    Generuje kody QR. Zapisuje w folderze ./pos/
    :param num_to_gen: liczba kodów [i obrazów] do wygenerowania
    :return:
    """

    import qrcode

    for i in range(num_to_gen):
        input_data = str(((i * 2 + 31) ** 5) % 100000000)
        #print(input_data)
        qr = qrcode.QRCode(
            version=2,
            box_size=2,
            border=5)
        qr.add_data(input_data)
        qr.make(fit=True)
        img = qr.make_image(fill='black', back_color='white')
        img.save('pos/' + str(i) + '.png')


# pip install simple_image_download
def download_images(name, num_to_download):
    """
    Pobieranie obrazów z google. Zapisuje w ./simple_images/name
    :param name: słowa kluczowe do wyszukania, można wiele - oddzielić przecinkiem np.: 'Yoda, Kenobi, R2-D2'
    :return: nic
    """

    from simple_image_download import simple_image_download as simp

    response = simp.simple_image_download

    response().download(name, num_to_download)

    # print(response().urls(name, num_to_download))

# pip install python-resize-image
def generate_neg(name):
    """
    Zmienia rozmiar pobranych obrazów
    :param name: nazwa obrazów - podane wcześniej słowo kluczowe - tylko jedno hasło (np. 'Yoda' albo 'Kenobi', ale nie 'Yoda, Kenobi')
    :return: nic
    """
    from PIL import Image
    from resizeimage import resizeimage

    import os

    files = []
    for (_, _, filenames) in os.walk('simple_images/' + name):
        files.extend(filenames)
        break

    fil = open('bg.txt', "w")

    for i in range(len(files)):
        filename, file_ext = os.path.splitext('simple_images/' + name + '/' + files[i])
        with open(filename + file_ext, 'r+b') as f:
            with Image.open(f) as image:
                cover = resizeimage.resize_cover(image, [140, 140])
                cover.save('neg/' + str(i + 1) + file_ext, image.format)
                fil.write('neg/' + str(i + 1) + file_ext + '\n')
    fil.close()


def pos_info_file():
    fi = open('info.dat', "w")
    for i in range(2000):
        fi.write('pos/' + str(i + 1) + '.png 1 0 0 70 70\n')
    fi.close()

print('Generowanie kodów QR')
generate_qr(4000)

print('Zapis pos do pliku')
pos_info_file()

print('Pobieranie obrazów')
download_images('bed', 2000)

print('Przekształcanie obrazów')
generate_neg('bed')

print("Koniec!")

# po wykonaniu programu należy wykonać komendy:
# sciezka_do_pobranego_opencv\opencv\build\x64\vc15\bin\opencv_createsamples.exe -info info.dat -w 24 -h 24 -num 1000 -vec pos.vec
# sciezka_do_pobranego_opencv\opencv\build\x64\vc15\bin\opencv_traincascade.exe -data cascade/ -vec pos.vec -bg bg.txt -w 24 -h 24 -numPos 1000 -numNeg 500 -numStages 10
# dla lepszego efektu chyba trzeba pobawić się parametrami tych komend, wygenerować więcej qr, pobrać więcej negative samples, /shrug
# ten plik co będziemy z niego korzystali to cascade.xml w folderze cascade
