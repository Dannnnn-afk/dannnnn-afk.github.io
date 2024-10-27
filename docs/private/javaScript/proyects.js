document.addEventListener("DOMContentLoaded", () => {
  const tham = document.querySelector(".tham");
  const mobileMenu = document.getElementById("mobile-menu");

  if (tham && mobileMenu) {
    tham.addEventListener("keydown", (event) => {
      if (event.key === "Enter" || event.key === " ") {
        event.preventDefault();
        tham.classList.toggle("tham-active");
        mobileMenu.classList.toggle("hidden");
      }
    });

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
          el.textContent = el.getAttribute('data-en');
        });
        btnLang.textContent = 'Cambiar a Español';
        currentLang = 'en';
      } else {
        elements.forEach(el => {
          el.textContent = el.getAttribute('data-es');
        });
        btnLang.textContent = 'Change to English';
        currentLang = 'es';
      }
    });
  } else {
    console.error("Elemento 'btn-lang' no encontrado.");
  }

  function toggleCode(id) {
    const codeElement = document.getElementById(id);
    if (codeElement) {
      if (codeElement.classList.contains('hidden')) {
        codeElement.classList.remove('hidden');
      } else {
        codeElement.classList.add('hidden');
      }
    } else {
      console.error(`Elemento con id '${id}' no encontrado.`);
    }
  }

  // Expose toggleCode function to global scope
  window.toggleCode = toggleCode;
});