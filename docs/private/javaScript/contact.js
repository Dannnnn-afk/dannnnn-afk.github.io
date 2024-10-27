document.getElementById('commentForm').addEventListener('submit', function(event) {
  event.preventDefault();

  const name = document.getElementById('name').value;
  const email = document.getElementById('email').value;
  const comment = document.getElementById('comment').value;

  const comments = JSON.parse(localStorage.getItem('comments')) || [];
  comments.push({ name, email, comment });
  localStorage.setItem('comments', JSON.stringify(comments));

  alert('Comment submitted successfully!');
  displayComments();
});

function displayComments() {
  const commentsList = document.getElementById('commentsList');
  const comments = JSON.parse(localStorage.getItem('comments')) || [];

  commentsList.innerHTML = '';
  comments.forEach((comment, index) => {
    const commentDiv = document.createElement('div');
    commentDiv.classList.add('mb-4', 'p-4', 'bg-myGrey', 'rounded-md');
    commentDiv.innerHTML = `
      <p><strong data-en="Name:" data-es="Nombre:">Name:</strong> ${comment.name}</p>
      <p><strong data-en="Email:" data-es="Correo Electrónico:">Email:</strong> ${comment.email}</p>
      <p><strong data-en="Comment:" data-es="Comentario:">Comment:</strong> ${comment.comment}</p>
    `;
    commentsList.appendChild(commentDiv);
  });
}

// Initial display of comments
displayComments();

const tham = document.querySelector(".tham");
const mobileMenu = document.getElementById("mobile-menu");

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


// Language switcher
const btnLang = document.getElementById('btn-lang');
const elements = document.querySelectorAll('[data-en]');

let currentLang = 'es';

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