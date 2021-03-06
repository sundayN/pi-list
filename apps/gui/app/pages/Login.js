import React, { Component } from 'react';
import api from 'utils/api';
import Button from 'components/common/Button';
import Alert from 'components/common/Alert';
import AsyncErrorsManager from 'components/AsyncErrorsManager';
import keyEnum from 'enums/keyEnum';
import { translate } from 'utils/translation';
import { client } from '../utils/api';

class Login extends Component {
    constructor() {
        super();

        this.onClickLogin = this.onClickLogin.bind(this);
        this.onKeyUpEnter = this.onKeyUpEnter.bind(this);
        this.onClickRegister = this.onClickRegister.bind(this);

        this.state = {
            errors: [],
            userSuccessfullyRegistered: false,
        };
    }

    componentDidMount() {
        document.addEventListener(keyEnum.EVENTS.KEY_UP, this.onKeyUpEnter);
    }

    componentWillUnmount() {
        document.removeEventListener(keyEnum.EVENTS.KEY_UP, this.onKeyUpEnter);
    }

    onClickLogin() {
        const username = this.username.value;
        const password = this.password.value;

        client
            .login(username, password)
            .then(() => {
                this.props.history.push('/');
            })
            .catch(() => {
                this.setState({ errors: ['Login failed'] });
            });
    }

    onKeyUpEnter(event) {
        if (event.code === keyEnum.ENTER) {
            return this.onClickLogin();
        }
    }

    onClickRegister() {
        const username = this.username.value;
        const password = this.password.value;

        api.register({ username: username, password: password })
            .then(() => {
                this.setState({ userSuccessfullyRegistered: true, errors: [] });
            })
            .catch(error => {
                this.setState({
                    errors: [error],
                    userSuccessfullyRegistered: false,
                });
            });
    }

    render() {
        return (
            <div className="lst-login--container row center-xs middle-xs fade-in">
                <div className="lst-login--logo lst-text-center">
                    <img src="/static/ebu_logo.svg" alt="EBU List logo" height="45px" />
                </div>
                <div className="lst-login--logo lst-text-center">
                    <b>LIST</b> - LiveIP Software Toolkit
                </div>
                <div className="lst-login--form lst-text-center">
                    <h1 className="lst-login--header">{translate('user_account.sign_in')}</h1>
                    <div className="lst-login--group">
                        <input
                            className="lst-input"
                            ref={ref => (this.username = ref)}
                            type="username"
                            placeholder={translate('user_account.email')}
                        />
                    </div>
                    <div className="lst-login--group">
                        <input
                            className="lst-input"
                            ref={ref => (this.password = ref)}
                            type="password"
                            placeholder={translate('user_account.password')}
                        />
                    </div>

                    <div className="lst-login--group lst-no-margin">
                        {this.state.userSuccessfullyRegistered && (
                            <Alert type="success" showIcon>
                                {translate('user_account.user_registered_message')}
                            </Alert>
                        )}
                        <AsyncErrorsManager errors={this.state.errors} />
                    </div>

                    <div className="lst-login--group lst-margin--bottom-2">
                        <div className="col-xs-6 lst-no-padding lst-padding--right-10">
                            <Button
                                className="lst-login-btn"
                                outline
                                label={translate('buttons.register')}
                                onClick={this.onClickRegister}
                                noMargin
                            />
                        </div>
                        <div className="col-xs-6 lst-no-padding lst-padding--left-10">
                            <Button
                                className="lst-login-btn"
                                type="info"
                                label={translate('buttons.login')}
                                onClick={this.onClickLogin}
                                noMargin
                            />
                        </div>
                    </div>
                </div>
            </div>
        );
    }
}

export default Login;
