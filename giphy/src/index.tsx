import * as React from 'react';
import * as ReactDOM from 'react-dom';

import App from './App';
import './styles.scss';
import './styles/app3.scss'

var mountNode = document.getElementById('app');
ReactDOM.render(<App name="Giphy Search" />, mountNode);
