from PIL import Image, ImageEnhance
import fitz  # PyMuPDF

img_path = r"C:\Users\Administrador\Downloads\plano_movimentacao_de_cargas.jpeg"
pdf_path = r"C:\Users\Administrador\Downloads\plano_movimentacao_carga_revitalizado.pdf"
temp_img_path = r"C:\Users\Administrador\Downloads\temp_img.png"

# Abrir imagem
image = Image.open(img_path)

# Aumentar contraste e brilho
image = ImageEnhance.Contrast(image).enhance(1.2)
image = ImageEnhance.Brightness(image).enhance(1.1)

# Dimensões A4 em pontos
a4_width, a4_height = 595, 842
image_ratio = image.width / image.height
a4_ratio = a4_width / a4_height

if image_ratio > a4_ratio:
    new_width = a4_width
    new_height = int(a4_width / image_ratio)
else:
    new_height = a4_height
    new_width = int(a4_height * image_ratio)

image_resized = image.resize((new_width, new_height), Image.LANCZOS)

# Salvar temporariamente a imagem redimensionada para inserir no PDF
image_resized.save(temp_img_path)

# Criar PDF e inserir imagem centralizada
pdf = fitz.open()
page = pdf.new_page(width=a4_width, height=a4_height)

x_offset = (a4_width - new_width) / 2
y_offset = (a4_height - new_height) / 2

page.insert_image(
    rect=(x_offset, y_offset, x_offset + new_width, y_offset + new_height),
    filename=temp_img_path
)

pdf.save(pdf_path)
pdf.close()

print(f"PDF gerado em: {pdf_path}")
