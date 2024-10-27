/** @type {import('tailwindcss').Config} */
module.exports = {
  content: ["./public/*.html"],
  theme: {
    colors: {
      'myBlack': '#191516',
      'myWhite': '#DFE2CF',
      'myPurple': '#BEB8EB',
      'myGrey': '#2F323A',
      'myRed': '#C33C54',
      'myBlue': '#1E96FC',
    },
    boxShadow: {
      '2xl': '0 10px 25px rgba(0, 0, 0, 0.25)',
      myBlack: '0 0 10px #000000',
    },
    keyframes: {
      borderAnimation: {
        '0%, 100%': { borderColor: 'transparent' },
        '50%': { borderColor: '#1E96FC' },
      },
    },
    animation: {
      border: 'borderAnimation 2s infinite',
    },
  },
  variants: {
    extend: {
      transform: ['group-hover'],
      scale: ['group-hover'],
      rotate: ['group-hover'],
      boxShadow: ['group-hover'],
      borderColor: ['group-hover'],
    },
  },
  
  plugins: [require('tailwind-hamburgers')],
}