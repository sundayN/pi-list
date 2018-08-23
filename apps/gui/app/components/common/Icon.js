import React from 'react';
import PropTypes from 'prop-types';
import classNames from 'classnames';

const propTypes = {
    value: PropTypes.string.isRequired,
    className: PropTypes.string
};

const defaultProps = {
    className: ''
};

const Icon = (props) => {
    const iconClassName = classNames(
        'lst-icons',
        props.className,
        {
            'recording-animation': props.value === 'fiber_manual_record',
            'device-search-animation': props.value === 'wifi_tethering'
        }
    );

    const materialIconName = props.value.replace(/ /g, '_');

    return (
        <i className={iconClassName}>
            {materialIconName}
        </i>
    );
};

Icon.propTypes = propTypes;
Icon.defaultProps = defaultProps;

export default Icon;
