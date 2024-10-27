document.addEventListener("DOMContentLoaded", () => {
  const tham = document.querySelector(".tham");
  const mobileMenu = document.getElementById("mobile-menu");

  if (tham && mobileMenu) {
    tham.addEventListener("click", () => {
      tham.classList.toggle("tham-active");
      mobileMenu.classList.toggle("hidden");
    });
  } else {
    console.error("Elementos 'tham' o 'mobileMenu' no encontrados.");
  }

  // Language switcher
  const btnLang = document.getElementById('btn-lang');
  const elements = document.querySelectorAll('[data-en]');

  let currentLang = 'es';

  if (btnLang) {
    btnLang.addEventListener('click', () => {
      if (currentLang === 'es') {
        elements.forEach(el => {
          const enText = el.getAttribute('data-en');
          if (enText) {
            el.textContent = enText;
          } else {
            console.warn(`Elemento ${el} no tiene atributo 'data-en'.`);
          }
        });
        btnLang.textContent = 'Cambiar a Español';
        currentLang = 'en';
      } else {
        elements.forEach(el => {
          const esText = el.getAttribute('data-es');
          if (esText) {
            el.textContent = esText;
          } else {
            console.warn(`Elemento ${el} no tiene atributo 'data-es'.`);
          }
        });
        btnLang.textContent = 'Change to English';
        currentLang = 'es';
      }
    });
  } else {
    console.error("Elemento 'btn-lang' no encontrado.");
  }

  const btnCertificaciones = document.getElementById('btn-certificaciones');
  const pdfList = document.getElementById('pdf-list');

  if (btnCertificaciones && pdfList) {
    btnCertificaciones.addEventListener('click', () => {
      pdfList.classList.toggle('hidden');
    });
  } else {
    console.error("Elementos 'btn-certificaciones' o 'pdf-list' no encontrados.");
  }
});